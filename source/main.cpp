#include "studentmanger.h"
#include "TeacherManager.h"

#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	StudentManger w;	
	w.show();

	/*TeacherManager w;
	w.show();*/

   return a.exec();	
		
}
