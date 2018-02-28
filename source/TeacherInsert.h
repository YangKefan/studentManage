#ifndef TEACHERINSERT_H
#define TEACHERINSERT_H

#include "ui_TeacherInsert.h"
#include "GBK.h"

#include <QWidget>
#include <QWidget>
#include <QDebug>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QSqlRecord>

class TeacherInsert : public QWidget
{
	Q_OBJECT

public:
	TeacherInsert(QWidget *parent = 0);
	~TeacherInsert();
	bool judgeEmpty();
	void clearAll();
private:
	Ui::TeacherInsert ui;
	QSqlTableModel *model; 

signals:
	void EmitToTeacherManage();

private slots:
	void returnBtnSlot();
	void confirmBtnSlot();

};

#endif // TEACHERINSERT_H
