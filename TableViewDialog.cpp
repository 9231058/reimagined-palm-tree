#include <QtGui>
#include "Course.h"
#include "TableViewDialog.h"

TableViewDialog::TableViewDialog(int no,QWidget* parent):QDialog(parent){
	setupUi(this);
	QString fileName;
	QTextStream stringOut(&fileName);
	stringOut<<"students/"<<no<<".txt";
	QFile file(fileName);
	file.open(QIODevice::ReadOnly);
	QDataStream in(&file);
	Course* Old=new Course();
	while(!file.atEnd()){
		in>>Old->CourseName>>Old->TeacherName>>Old->No>>Old->Day1>>Old->Start1>>Old->End1>>Old->Day2>>Old->Start2>>Old->End2;
		int i=Old->Start1-7;
		while(i<Old->End1-7){
			tableView->setItem(Old->Day1,i,new QTableWidgetItem(Old->CourseName));
			i++;
		}
		i=Old->Start2-7;
		while(i<Old->End2-7){
			tableView->setItem(Old->Day2,i,new QTableWidgetItem(Old->CourseName));
			i++;
		}
	}
	file.close();
}
