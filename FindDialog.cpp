#include <QtGui>
#include <QString>
#include "FindDialog.h"
#include "Student.h"
#include "Course.h"

static QString DAY[]={"Invalid","Saturday","Sunday","Monday","Tuesday","Wednesday","Thursday","Friday"};

FindDialog::FindDialog(QWidget* parent):QDialog(parent){
	setupUi(this);
	QRegExp regExp1("[0-9]{1,10}");
	QRegExp regExp2("[A-Za-z]{1,50}");
	QRegExp regExp3("[A-Za-z]{1,50}");
	lineEdit->setValidator(new QRegExpValidator(regExp1,this));
	lineEdit_2->setValidator(new QRegExpValidator(regExp2,this));
	lineEdit_3->setValidator(new QRegExpValidator(regExp3,this));
	connect(studentButton,SIGNAL(clicked()),this,SLOT(student_button_press()));
	connect(courseButton,SIGNAL(clicked()),this,SLOT(course_button_press()));
	connect(findButton,SIGNAL(clicked()),this,SLOT(find_button_press()));
}
void FindDialog::course_button_press(){
	if(studentButton->isChecked()==true){
		studentButton->setChecked(false);
		label->setText("Course Number");
		label_2->setText("Course Name");
		label_3->setText("Teacher Name");
	}
	else
		courseButton->setChecked(true);
}
void FindDialog::student_button_press(){
	if(courseButton->isChecked()==true){
		courseButton->setChecked(false);
		label->setText("Student Number");
		label_2->setText("First Name");
		label_3->setText("Last Name");
	}
	else
		studentButton->setChecked(true);
}
void FindDialog::on_lineEdit_textChanged(){
	findButton->setEnabled(lineEdit->hasAcceptableInput()||lineEdit_2->hasAcceptableInput()||lineEdit_3->hasAcceptableInput());
}
void FindDialog::on_lineEdit_2_textChanged(){
	findButton->setEnabled(lineEdit->hasAcceptableInput()||lineEdit_2->hasAcceptableInput()||lineEdit_3->hasAcceptableInput());
}
void FindDialog::on_lineEdit_3_textChanged(){
	findButton->setEnabled(lineEdit->hasAcceptableInput()||lineEdit_2->hasAcceptableInput()||lineEdit_3->hasAcceptableInput());
}
void FindDialog::find_button_press(){
	list->clear();
	bool hasName1=1;
	bool hasName2=1;
	bool hasInt=1;
	QString Name1;
	Name1.insert(0,lineEdit_2->text());
	QString Name2;
	Name2.insert(0,lineEdit_3->text());
	int Int=0;
	if(!Name1.isEmpty())
		hasName1=0;
	if(!Name2.isEmpty())
		hasName2=0;
	if(!(lineEdit->text()).isEmpty()){
		hasInt=0;
		Int=(lineEdit->text()).toInt();
	}
	QStringList stringList;
	if(studentButton->isChecked()){
		Student* Old=new Student();
		QFile file("students.txt");
		file.open(QIODevice::ReadOnly);
		QDataStream in(&file);
		while(!file.atEnd()){
			in>>Old->FirstName>>Old->LastName>>Old->No;
			if(hasName1||(Old->FirstName).compare(Name1,Qt::CaseInsensitive)==0)
				if(hasName2||(Old->LastName).compare(Name2,Qt::CaseInsensitive)==0)
					if(hasInt||Old->No==Int)
						stringList<<Old->FirstName<<Old->LastName<<QString::number(Old->No);
		}
	}
	else{
		Course* Old=new Course();
		QFile file("courses.txt");
		file.open(QIODevice::ReadOnly);
		QDataStream in(&file);
		while(!file.atEnd()){
			in>>Old->CourseName>>Old->TeacherName>>Old->No>>Old->Day1>>Old->Start1>>Old->End1>>Old->Day2>>Old->Start2>>Old->End2;
			if(hasName1||(Old->CourseName).compare(Name1,Qt::CaseInsensitive)==0)
				if(hasName2||(Old->TeacherName).compare(Name2,Qt::CaseInsensitive)==0)
					if(hasInt||Old->No==Int)
						stringList<<Old->CourseName<<Old->TeacherName<<QString::number(Old->No)<<DAY[Old->Day1]<<QString::number(Old->Start1)<<QString::number(Old->End2)<<DAY[Old->Day1]<<QString::number(Old->Start2)<<QString::number(Old->End2);
		}
	}
	list->addItems(stringList);
}
