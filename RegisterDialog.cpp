#include <QtGui>
#include <QString>
#include <QFile>
#include <algorithm>
#include "Student.h"
#include "Course.h"
#include "RegisterDialog.h"

static QString DAY[]={"Invalid","Saturday","Sunday","Monday","Tuesday","Wednesday","Thursday","Friday"};

RegisterDialog::RegisterDialog(QWidget *parent,int no):QDialog(parent){
	setupUi(this);
	QFile file("students.txt");
	int find=0;
	Student* Old=new Student();
	if(file.open(QIODevice::ReadOnly)){
		QDataStream in(&file);
		while(!file.atEnd()){
			in>>Old->FirstName>>Old->LastName>>Old->No;
			if(Old->No==no){
				find=1;
				break;
			}
		}
	}
	this->student=Old;
	if(find==0){
		QMessageBox::warning(this,tr("Register"),tr("Your student number is wrong"),QMessageBox::Cancel|QMessageBox::Escape);
		this->validNo=false;
		label->setText("Please back before anything goes wrong ..");
	}
	else{
		this->validNo=true;
		label->setText("Hello "+Old->FirstName+' '+Old->LastName);
	}
	QRegExp regExp("[0-9]{1,10}");
	lineEdit->setValidator(new QRegExpValidator(regExp,this));
	connect(registerButton,SIGNAL(clicked()),this,SLOT(register_button_press()));
	connect(listButton,SIGNAL(clicked()),this,SLOT(list_button_press()));
}
void RegisterDialog::on_lineEdit_textChanged(){
	registerButton->setEnabled(lineEdit->hasAcceptableInput()&&validNo);
}
void RegisterDialog::register_button_press(){
	QString StringNo=lineEdit->text();
	int CourseNo=StringNo.toInt();
	lineEdit->setText("");
	QFile file1("courses.txt");
	file1.open(QIODevice::ReadOnly);
	int find=0;
	Course* Old=new Course;
	QDataStream in1(&file1);
	while(!file1.atEnd()){
		in1>>Old->CourseName>>Old->TeacherName>>Old->No>>Old->Day1>>Old->Start1>>Old->End1>>Old->Day2>>Old->Start2>>Old->End2;
		if(Old->No==CourseNo){
			find=1;
			break;
		}
	}
	file1.close();
	if(find==0){
		QMessageBox::warning(this,tr("Register"),tr("Your course number is wrong"),QMessageBox::Cancel|QMessageBox::Escape|QMessageBox::Default);
	}
	else if(this->check_course(*Old)){
		int grade=0;
		QString fileName;
		QTextStream stringOut(&fileName);
		stringOut<<"students/"<<student->No<<".txt";
		QFile file2(fileName);
		file2.open(QIODevice::Append);
		QDataStream out2(&file2);
		out2<<Old->CourseName<<Old->TeacherName<<quint32(Old->No)<<quint32(Old->Day1)<<quint32(Old->Start1)<<quint32(Old->End1)<<quint32(Old->Day2)<<quint32(Old->Start2)<<quint32(Old->End2);
		file2.close();
		fileName.clear();
		stringOut<<"courses/"<<Old->No<<".txt";
		QFile file3(fileName);
		file3.open(QIODevice::Append);
		QDataStream out3(&file3);
		out3<<student->FirstName<<student->LastName<<quint32(student->No)<<quint32(grade);
		file3.close();
		QMessageBox::information(this,tr("Register"),"You are successfully register in "+Old->CourseName,QMessageBox::Cancel|QMessageBox::Default);

	}
	else{
		QMessageBox::warning(this,tr("Register"),tr("You can not have this course"),QMessageBox::Cancel|QMessageBox::Escape|QMessageBox::Default);
	}
}
void RegisterDialog::list_button_press(){
	list->clear();
	QString fileName;
	QTextStream stringOut(&fileName);
	stringOut<<"students/"<<student->No<<".txt";
	QFile file(fileName);
	file.open(QIODevice::ReadOnly);
	QDataStream in(&file);
	Course* Old=new Course();
	QStringList course;
	while(!file.atEnd()){
		in>>Old->CourseName>>Old->TeacherName>>Old->No>>Old->Day1>>Old->Start1>>Old->End1>>Old->Day2>>Old->Start2>>Old->End2;
		course<<Old->CourseName<<Old->TeacherName<<QString::number(Old->No)<<DAY[Old->Day1]<<QString::number(Old->Start1)<<QString::number(Old->End1)<<DAY[Old->Day2]<<QString::number(Old->Start2)<<QString::number(Old->End2);
	}
	list->addItems(course);
}
bool RegisterDialog::check_time(Course c1,Course c2){
	if(c1.Day1==c2.Day1){
		if((c1.End1-c1.Start1)+(c2.End1-c2.Start1)>std::max(c1.End1,c2.End1)-std::min(c1.Start1,c2.Start1))
			return false;
	}
	if(c1.Day2==c2.Day1){
		if((c1.End2-c1.Start2)+(c2.End1-c2.Start1)>std::max(c1.End2,c2.End1)-std::min(c1.Start2,c2.Start1))
			return false;
	}
	if(c1.Day1==c2.Day2){
		if((c1.End1-c1.Start1)+(c2.End2-c2.Start2)>std::max(c1.End1,c2.End2)-std::min(c1.Start1,c2.Start2))
			return false;
	}
	if(c1.Day2==c2.Day2){
		if((c1.End2-c1.Start2)+(c2.End2-c2.Start2)>std::max(c1.End2,c2.End2)-std::min(c1.Start2,c2.Start2))
			return false;
	}
	return true;
}
bool RegisterDialog::check_course(Course c){
	QString fileName;
	QTextStream stringOut(&fileName);
	stringOut<<"students/"<<student->No<<".txt";
	QFile file(fileName);
	file.open(QIODevice::ReadOnly);
	QDataStream in(&file);
	Course* Old=new Course();
	bool problem=false;
	while(!file.atEnd()){
		in>>Old->CourseName>>Old->TeacherName>>Old->No>>Old->Day1>>Old->Start1>>Old->End1>>Old->Day2>>Old->Start2>>Old->End2;
		if(!check_time(c,*Old)){
			problem=true;
			break;
		}
	}
	if(!problem)
		return true;
	else
		return false;
}
