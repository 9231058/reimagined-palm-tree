#include <QtGui>
#include <QString>
#include <QFile>
#include "CourseDialog.h"
#include "Course.h"

static QString DAY[]={"Invalid","Saturday","Sunday","Monday","Tuesday","Wednesday","Thursday","Friday"};

CourseDialog::CourseDialog(QWidget* parent):QDialog(parent){
	setupUi(this);
	QRegExp regExp1("[A-Za-z]{1,50}");
	QRegExp regExp2("[A-Za-z]{1,50}");
	QRegExp regExp3("[0-9]{1,10}");
	QRegExp regExp4("[1-7]{1,1} [0-9]{1,2} [0-9]{1,2}");
	QRegExp regExp5("[1-7]{0,1} [0-9]{0,2} [0-9]{0,2}");
	lineEdit->setValidator(new QRegExpValidator(regExp1,this));
	lineEdit_2->setValidator(new QRegExpValidator(regExp2,this));
	lineEdit_3->setValidator(new QRegExpValidator(regExp3,this));
	lineEdit_4->setValidator(new QRegExpValidator(regExp4,this));
	lineEdit_5->setValidator(new QRegExpValidator(regExp5,this));
	connect(addButton,SIGNAL(clicked()),this,SLOT(add_button_press()));
	connect(listButton,SIGNAL(clicked()),this,SLOT(list_button_press()));
}
void CourseDialog::on_lineEdit_textChanged(){
	addButton->setEnabled(lineEdit->hasAcceptableInput()&&lineEdit_2->hasAcceptableInput()&&lineEdit_3->hasAcceptableInput()&&lineEdit_4->hasAcceptableInput()&&lineEdit_5->hasAcceptableInput());
}
void CourseDialog::on_lineEdit_2_textChanged(){
	addButton->setEnabled(lineEdit->hasAcceptableInput()&&lineEdit_2->hasAcceptableInput()&&lineEdit_3->hasAcceptableInput()&&lineEdit_4->hasAcceptableInput()&&lineEdit_5->hasAcceptableInput());
}
void CourseDialog::on_lineEdit_3_textChanged(){
	addButton->setEnabled(lineEdit->hasAcceptableInput()&&lineEdit_2->hasAcceptableInput()&&lineEdit_3->hasAcceptableInput()&&lineEdit_4->hasAcceptableInput()&&lineEdit_5->hasAcceptableInput());
}
void CourseDialog::on_lineEdit_4_textChanged(){
	addButton->setEnabled(lineEdit->hasAcceptableInput()&&lineEdit_2->hasAcceptableInput()&&lineEdit_3->hasAcceptableInput()&&lineEdit_4->hasAcceptableInput()&&lineEdit_5->hasAcceptableInput());
}
void CourseDialog::on_lineEdit_5_textChanged(){
	addButton->setEnabled(lineEdit->hasAcceptableInput()&&lineEdit_2->hasAcceptableInput()&&lineEdit_3->hasAcceptableInput()&&lineEdit_4->hasAcceptableInput()&&lineEdit_5->hasAcceptableInput());
}
void CourseDialog::add_button_press(){
	Course* New=new Course();
	(New->CourseName).insert(0,lineEdit->text());
	(New->TeacherName).insert(0,lineEdit_2->text());
	New->No=(lineEdit_3->text()).toInt();
	QString TimeClass1=lineEdit_4->text();
	QString TimeClass2=lineEdit_5->text();
	QTextStream stringIn1(&TimeClass1);
	stringIn1>>New->Day1>>New->Start1>>New->End1;
	QTextStream stringIn2(&TimeClass2);
	stringIn2>>New->Day2>>New->Start2>>New->End2;
	QFile file1("courses.txt");
	file1.open(QIODevice::Append);
	QDataStream out1(&file1);
	out1<<New->CourseName<<New->TeacherName<<quint32(New->No)<<quint32(New->Day1)<<quint32(New->Start1)<<quint32(New->End1)<<quint32(New->Day2)<<quint32(New->Start2)<<quint32(New->End2);
	file1.close();
	QString fileName;
	QTextStream stringOut(&fileName);
	stringOut<<"courses/"<<New->No<<".txt";
	QFile file2(fileName);
	file2.open(QIODevice::WriteOnly);
	file2.close();
	lineEdit->setText("");
	lineEdit_2->setText("");
	lineEdit_3->setText("");
	lineEdit_4->setText("");
	lineEdit_5->setText("");
}
void CourseDialog::list_button_press(){
	list->clear();
	Course* Old=new Course();
	QFile file("courses.txt");
	file.open(QIODevice::ReadOnly);
	QDataStream in(&file);
	QStringList course;
	while(!file.atEnd()){
		in>>Old->CourseName>>Old->TeacherName>>Old->No>>Old->Day1>>Old->Start1>>Old->End1>>Old->Day2>>Old->Start2>>Old->End2;
		course<<Old->CourseName<<Old->TeacherName<<QString::number(Old->No)<<DAY[Old->Day1]<<QString::number(Old->Start1)<<QString::number(Old->End1)<<DAY[Old->Day2]<<QString::number(Old->Start2)<<QString::number(Old->End2);
	}
	list->addItems(course);
}
