#ifndef GRADEDIALOG_H
#define GRADEDIALOG_H

#include <QVector>
#include <QDialog>
#include "ui_gradedialog.h"
#include "Student.h"

class Course;

class GradeDialog:public QDialog,protected Ui::GradeDialog{
	Q_OBJECT
	public:
		GradeDialog(int no,QWidget* parent=0);
	private slots:
		void update_button_press();
		void on_lineEdit_textChanged();
		void on_lineEdit_2_textChanged();
	private:
		void update_list();
		bool validNo;
		Course* course;
		QVector <Student> studentVector;
		QVector <int> gradeVector;
};
#endif
