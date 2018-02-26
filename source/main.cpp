#include "studentmanger.h"
#include "logindialog.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	StudentManger w;	
    w.show();

   return a.exec();	
		
}
