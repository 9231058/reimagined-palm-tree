#ifndef COURSEDIALOG_H
#define COURSEDIALOG_H
#include <QDialog>
#include "ui_coursedialog.h"

class CourseDialog:public QDialog,public Ui::CourseDialog{
	Q_OBJECT
	public:
		CourseDialog(QWidget* parent=0);
	private slots:
		void list_button_press();
		void add_button_press();
		void on_lineEdit_textChanged();
		void on_lineEdit_2_textChanged();
		void on_lineEdit_3_textChanged();
		void on_lineEdit_4_textChanged();
		void on_lineEdit_5_textChanged();
};
#endif
