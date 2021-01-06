#include <QtGui>
#include "GradeDialog.h"
#include "Course.h"
#include "Student.h"

GradeDialog::GradeDialog(int no,QWidget* parent):QDialog(parent){
	setupUi(this);
	course=new Course();
	QFile file1("courses.txt");
	int find=0;
	if(file1.open(QIODevice::ReadOnly)){
		QDataStream in1(&file1);
		while(!file1.atEnd()){
			in1>>(this->course)->CourseName>>(this->course)->TeacherName>>(this->course)->No>>(this->course)->Day1>>(this->course)->Start1>>(this->course)->End1>>(this->course)->Day2>>(this->course)->Start2>>(this->course)->End2;
			if(course->No==no){
				find=1;
				break;
			}
		}
	}
	file1.close();
	if(!find){
		QMessageBox::warning(this,tr("Register"),tr("Your course number is wrong"),QMessageBox::Cancel|QMessageBox::Escape);
		this->validNo=false;
	}
	else{
		this->validNo=true;
		QString fileName;
		QTextStream stringOut(&fileName);
		stringOut<<"courses/"<<no<<".txt";
		QFile file2(fileName);
		file2.open(QIODevice::ReadOnly);
		QDataStream in2(&file2);
		Student Old;
		int gradeOld;
		while(!file2.atEnd()){
			in2>>Old.FirstName>>Old.LastName>>Old.No>>gradeOld;
			(this->studentVector).push_back(Old);
			(this->gradeVector).push_back(gradeOld);
		}
		file2.close();
		update_list();
	}
	QRegExp regExp1("[0-9]{1,10}");
	QRegExp regExp2("[0-9]{1,2}");
	lineEdit->setValidator(new QRegExpValidator(regExp1,this));
	lineEdit_2->setValidator(new QRegExpValidator(regExp2,this));
	connect(updateButton,SIGNAL(clicked()),this,SLOT(update_button_press()));
}
void GradeDialog::update_list(){
	list->clear();
	for(int i=0;i<(this->studentVector).size();i++){
		Student temp=(this->studentVector)[i];
		int gradeOld=(this->gradeVector)[i];
		QListWidgetItem* item=new QListWidgetItem(temp.FirstName+'\n'+temp.LastName+'\n'+QString::number(temp.No)+'\n'+QString::number(gradeOld));
		list->addItem(item);
	}
}
void GradeDialog::on_lineEdit_textChanged(){
	updateButton->setEnabled(lineEdit->hasAcceptableInput()&&lineEdit_2->hasAcceptableInput()&&validNo);
}
void GradeDialog::on_lineEdit_2_textChanged(){
	updateButton->setEnabled(lineEdit->hasAcceptableInput()&&lineEdit_2->hasAcceptableInput()&&validNo);
}
void GradeDialog::update_button_press(){
	int studentNo=(lineEdit->text()).toInt();
	int newGrade=(lineEdit_2->text()).toInt();
	QString fileName;
	QTextStream stringOut(&fileName);
	stringOut<<"courses/"<<(this->course)->No<<".txt";
	QFile file(fileName);
	file.open(QIODevice::WriteOnly);
	QDataStream out(&file);	
	for(int i=0;i<(this->studentVector).size();i++){
		if((this->studentVector)[i].No==studentNo){
			(this->gradeVector)[i]=newGrade;
		}
		out<<(this->studentVector)[i].FirstName<<(this->studentVector)[i].LastName<<quint32((this->studentVector)[i].No)<<quint32((this->gradeVector)[i]);
	}
	update_list();
	file.close();
}
