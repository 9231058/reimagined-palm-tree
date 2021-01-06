#ifndef FINDDIALOG_H
#define FINDDIALOG_H
#include <QWidget>
#include "ui_finddialog.h"

class FindDialog:public QDialog,public Ui::FindDialog{
	Q_OBJECT
	public:
		FindDialog(QWidget* parent=0);
	private slots:
		void course_button_press();
		void student_button_press();
		void on_lineEdit_textChanged();
		void on_lineEdit_2_textChanged();
		void on_lineEdit_3_textChanged();
		void find_button_press();
};
#endif
