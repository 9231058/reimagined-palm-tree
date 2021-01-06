#ifndef TABLEVIEWDIALOG_H
#define TABLEVIEWDIALOG_H

#include <QDialog>
#include "ui_tableviewdialog.h"

class TableViewDialog:public QDialog,public Ui::TableViewDialog{
	Q_OBJECT
	public:
		TableViewDialog(int no,QWidget* parent=0);
};
#endif
