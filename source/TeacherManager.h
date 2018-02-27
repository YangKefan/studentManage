#ifndef TEACHERMANAGER_H
#define TEACHERMANAGER_H

#include "ui_TeacherManager.h"
#include"TeacherSearch.h"

#include <QWidget>
#include <QDebug>
#include <QTimer>
#include <QDatetime>

class TeacherManager : public QWidget
{
	Q_OBJECT

public:
	TeacherManager(QWidget *parent = 0);
	~TeacherManager();
	void setbtntrue();
	void setbtnfalse();

private:
	Ui::TeacherManager *ui;	
	QString teachername;
	QString teachernum;
	QTimer *timelinetimer;
	TeacherSearch *teachersearch;

signals:
	void toLoginDialog();
	void toTeaPassWord(QString);
	void toTeacherSearch();
	void toTeacherChangeScore();
	void toTeacherDelete();

private slots:
	void comeLoginDialog(QString,QString);
	void searchbtnSlot();
	void exitbtnSlot();
	void setbtnEnableSlot();
	void tosetStack();

};

#endif // TEACHERMANAGER_H
