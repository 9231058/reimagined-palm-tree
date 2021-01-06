#include <QtGui>
#include <QString>
#include <stdio.h>
#include "MainDialog.h"
#include "StudentDialog.h"
#include "GetNoDialog.h"
#include "RegisterDialog.h"
#include "CourseDialog.h"
#include "GradeDialog.h"
#include "FindDialog.h"
#include "TableViewDialog.h"

MainDialog::MainDialog(QWidget *parent):QDialog(parent){
	setupUi(this);
	connect(studentButton,SIGNAL(clicked()),this,SLOT(Student()));
	connect(registerButton,SIGNAL(clicked()),this,SLOT(Register()));
	connect(courseButton,SIGNAL(clicked()),this,SLOT(Course()));
	connect(resetButton,SIGNAL(clicked()),this,SLOT(Reset()));
	connect(findButton,SIGNAL(clicked()),this,SLOT(Find()));
	connect(gradeButton,SIGNAL(clicked()),this,SLOT(Grade()));
	connect(tableViewButton,SIGNAL(clicked()),this,SLOT(TableView()));
}
void MainDialog::Student(){
	StudentDialog dialog(this);
	dialog.exec();
}
void MainDialog::Register(){
	GetNoDialog *dialog=new GetNoDialog("Student Number",this);
	if(dialog->exec()){
		QString no=(dialog->lineEdit)->text();
		delete dialog;
		RegisterDialog *reg=new RegisterDialog(this,no.toInt());
		reg->exec();
		delete reg;
	}
}
void MainDialog::Grade(){
	GetNoDialog *dialog=new GetNoDialog("Course Number",this);
	if(dialog->exec()){
		QString no=(dialog->lineEdit)->text();
		delete dialog;
		GradeDialog *grade=new GradeDialog(no.toInt(),this);
		grade->exec();
		delete grade;
	}
}
void MainDialog::Course(){
	CourseDialog dialog(this);
	dialog.exec();
}
void MainDialog::Reset(){
	int resault=QMessageBox::warning(this,tr("Reset"),tr("This clear your data.\nDo you want to continue ?"),QMessageBox::Yes,QMessageBox::No|QMessageBox::Default|QMessageBox::Escape);
	if(resault==QMessageBox::Yes){
		system("rm students/*");
		system("rm courses/*");
		system("rm students.txt courses.txt");
	}
}
void MainDialog::Find(){
	FindDialog dialog(this);
	dialog.exec();
}
void MainDialog::TableView(){
	GetNoDialog *dialog=new GetNoDialog("Course Number",this);
	if(dialog->exec()){
		QString no=(dialog->lineEdit)->text();
		delete dialog;
		TableViewDialog *view=new TableViewDialog(no.toInt(),this);
		view->exec();
		delete view;
	}
}
