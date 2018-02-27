#ifndef STUDENTSCORE_H
#define STUDENTSCORE_H

#include "ui_StudentScore.h"
#include "GBK.h"

#include <QWidget>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QMessageBox>


class StudentScore : public QWidget
{
	Q_OBJECT

public:
	StudentScore(QWidget *parent = 0);
	~StudentScore();
	QString studentnum;

private:
	Ui::StudentScore *ui;
	QSqlTableModel *model;

signals:
	void EmitToStuManage();

private slots:
	void comeStudentManage(QString);
	void returnbtnSlot();
};

#endif // STUDENTSCORE_H
