#ifndef TEACHERSEARCH_H
#define TEACHERSEARCH_H

#include "ui_TeacherSearch.h"
#include "GBK.h"

#include <QWidget>
#include <QSqlTableModel>
#include <QButtonGroup>
#include <QMessageBox>
#include <QStringList>
#include <QTableWidgetItem>
#include <QDebug>


class TeacherSearch : public QWidget
{
	Q_OBJECT

public:
	TeacherSearch(QWidget *parent = 0);
	~TeacherSearch();

private:
	Ui::TeacherSearch *ui;
	QSqlTableModel *model_1, *model_2;
	QButtonGroup *radioBtnGroup;

private slots:
	void searchBtnSlot();
	void comeTeacherManage();
	void returnBtnSlot();
	void inputEditSlot(QString);
	void radioBtnGroupSlot(int);
	
signals:
	void EmitToTeacherManage();
	void EmitToTeacherManageToChangeStack();		

};

#endif // TEACHERSEARCH_H
