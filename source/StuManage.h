#ifndef STUMANAGE_H
#define STUMANAGE_H

#include "ui_StuManage.h"
#include "StudentScore.h"
#include "GBK.h"

#include <QWidget>
#include <QDebug>
#include <QPalette>
#include <QDateTime>
#include <QTimer>
#include <QMessageBox>


class StuManage : public QWidget
{
	Q_OBJECT

public:
	StuManage(QWidget *parent = 0);
	~StuManage();
	void btnsettrue();
	void btnsetfalse();

private:
	Ui::StuManage *ui;
	QString studentname,studentnum;
	QTimer *timelinetimer;
	StudentScore *studentscore;

signals:
	void tostudentname(QString);
	void toStuInfoSearch(QString);
	void toLoginDialog();
	void toStudentScore(QString);

private slots:
	void comeLoginDialogSlot(QString,QString);
	void exitbtnSlot();
	void scorebtnSlot();
	void setbtnEnable();
};

#endif // STUMANAGE_H
