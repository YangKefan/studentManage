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
	TeacherSearch *teachersearch;
private slots:
	 void searchbtnSlot();
	 void exitbtnSlot();

signals:
	 void toTeacherSearch();
};

#endif // TEACHERMANAGER_H
