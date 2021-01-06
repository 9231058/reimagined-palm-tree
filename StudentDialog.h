#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>

#include "ui_studentdialog.h"

class StudentDialog : public QDialog , public Ui::StudentDialog{
	Q_OBJECT
	public:
		StudentDialog(QWidget *parnet=0);
	private slots:
		void on_lineEdit_textChanged();
		void on_lineEdit_2_textChanged();
		void on_lineEdit_3_textChanged();
		void add_button_press();
		void list_button_press();
};
#endif
