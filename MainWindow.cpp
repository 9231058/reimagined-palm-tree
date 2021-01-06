#include <QtGui>
#include "MainDialog.h"
#include "MainWindow.h"

MainWindow::MainWindow(){
	MainDialog *dialog=new MainDialog();
	setCentralWidget(dialog);
	QAction* aboutQtAction=new QAction(tr("About &Qt"),this);
	connect(aboutQtAction,SIGNAL(triggered()),qApp,SLOT(aboutQt()));
	QMenu* helpMenu=menuBar()->addMenu(tr("&Help"));
	helpMenu->addAction(aboutQtAction);
	QAction* exitAction=new QAction(tr("&Exit"),this);
	exitAction->setShortcut(tr("Ctrl+Q"));
	QMenu* fileMenu=menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(exitAction);
	connect(exitAction,SIGNAL(triggered()),this,SLOT(close()));
}
