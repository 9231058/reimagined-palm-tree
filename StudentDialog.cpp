#include <QFile>
#include <QtGui>
#include <QString>
#include "StudentDialog.h"
#include "Student.h"

StudentDialog::StudentDialog(QWidget *parent):QDialog(parent){
	setupUi(this);
	QRegExp regExp1("[A-Za-z]{1,50}");
	QRegExp regExp2("[A-Za-z]{1,50}");
	QRegExp regExp3("[0-9]{1,10}");
	lineEdit->setValidator(new QRegExpValidator(regExp1,this));
	lineEdit_2->setValidator(new QRegExpValidator(regExp2,this));
	lineEdit_3->setValidator(new QRegExpValidator(regExp3,this));
	connect(addButton,SIGNAL(clicked()),this,SLOT(add_button_press()));
	connect(listButton,SIGNAL(clicked()),this,SLOT(list_button_press()));
}
void StudentDialog::on_lineEdit_textChanged(){
	addButton->setEnabled(lineEdit->hasAcceptableInput()&&lineEdit_2->hasAcceptableInput()&&lineEdit_3->hasAcceptableInput());
}
void StudentDialog::on_lineEdit_2_textChanged(){
	addButton->setEnabled(lineEdit->hasAcceptableInput()&&lineEdit_2->hasAcceptableInput()&&lineEdit_3->hasAcceptableInput());
}
void StudentDialog::on_lineEdit_3_textChanged(){
	addButton->setEnabled(lineEdit->hasAcceptableInput()&&lineEdit_2->hasAcceptableInput()&&lineEdit_3->hasAcceptableInput());
}
void StudentDialog::add_button_press(){
	Student* New=new Student();
	(New->FirstName).insert(0,lineEdit->text());
	(New->LastName).insert(0,lineEdit_2->text());
	QString No=lineEdit_3->text();
	New->No=No.toInt();
	QFile file1("students.txt");
	file1.open(QIODevice::Append);
	QDataStream out1(&file1);
	out1<<New->FirstName<<New->LastName<<quint32(New->No);
	file1.close();
	QString fileName;
	QTextStream stringOut(&fileName);
	stringOut<<"students/"<<New->No<<".txt";
	QFile file2(fileName);
	file2.open(QIODevice::WriteOnly);
	file2.close();
	lineEdit->setText("");
	lineEdit_2->setText("");
	lineEdit_3->setText("");
}
void StudentDialog::list_button_press(){
	list->clear();
	Student* Old=new Student();
	QFile file("students.txt");
	file.open(QIODevice::ReadOnly);
	QDataStream in(&file);
	QStringList student;
	while(!file.atEnd()){
		in>>Old->FirstName>>Old->LastName>>Old->No;
		student<<Old->FirstName<<Old->LastName<<QString::number(Old->No);
	}
	list->addItems(student);
}	
