#ifndef TEACHERCHANGESCORE_H
#define TEACHERCHANGESCORE_H

#include "ui_TeacherChangeScore.h"
#include "GBK.h"

#include <QWidget>
#include <QDebug>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QSqlRecord>


class TeacherChangeScore : public QWidget
{
	Q_OBJECT

public:
	TeacherChangeScore(QWidget *parent = 0);
	~TeacherChangeScore();

private:
	Ui::TeacherChangeScore *ui;
	QSqlTableModel *model;
	int judge;

signals:
	void EmitToTeacherManage();
	void EmitToTeacherManageToChangeStack();

private slots:
		void comeTeacherManage();
		void confirmbtnSlot();
		void returnbtnSlot();
		void judgeSlot(QModelIndex,QModelIndex);

};

#endif // TEACHERCHANGESCORE_H
