#include <QApplication>
#include "MainWindow.h"

int main(int argc,char* argv[]){
	system("mkdir students");
	system("mkdir courses");
	QApplication app(argc,argv);
	MainWindow *mainWindow=new MainWindow;
	mainWindow->show();
	return app.exec();
}
