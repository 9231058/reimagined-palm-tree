#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>
#include "ui_maindialog.h"

class MainDialog : public QDialog,public Ui::MainDialog{
	Q_OBJECT
	public:
		MainDialog(QWidget *parent=0);
	private slots:
		void Student();
		void Register();
		void Course();
		void Reset();
		void Find();
		void Grade();
		void TableView();
};
#endif
