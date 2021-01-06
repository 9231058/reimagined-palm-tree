#include <QtGui>
#include <QString>
#include "GetNoDialog.h"

GetNoDialog::GetNoDialog(QString Label,QWidget *parent):QDialog(parent){
	setupUi(this);
	label->setText(Label);
	QRegExp regExp("[0-9]{1,10}");
	lineEdit->setValidator(new QRegExpValidator(regExp,this));
}
void GetNoDialog::on_lineEdit_textChanged(){
	okButton->setEnabled(lineEdit->hasAcceptableInput());
}
