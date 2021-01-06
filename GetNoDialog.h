#ifndef GETNODIALOG_H
#define GETNODIALOG_H

#include <QDialog>
#include "ui_getnodialog.h"

class QString;

class GetNoDialog : public QDialog,public Ui::GetNoDialog{
	Q_OBJECT
	public:
		GetNoDialog(QString Label,QWidget *parent=0);
	private slots:
		void on_lineEdit_textChanged();
};
#endif
