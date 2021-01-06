#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>
#include "ui_registerdialog.h"

class Student;
class Course;

class RegisterDialog : public QDialog , public Ui::RegisterDialog{
	Q_OBJECT
	public:
		RegisterDialog(QWidget *parent,int no);
	private:
		bool validNo;
		Student* student;
		static bool check_time(Course c1,Course c2);
		bool check_course(Course c);
	private slots:
		void register_button_press();
		void list_button_press();
		void on_lineEdit_textChanged();
};
#endif
