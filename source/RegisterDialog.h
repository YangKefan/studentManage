#ifndef REGSITERDIALOG_H
#define REGSITERDIALOG_H


#include "ui_RegsiterDialog.h"

#include <QDialog>
#include <QDebug>
#include <QPalette>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QTime>
#include <QMessageBox>
#include <QButtonGroup>


class RegisterDialog : public QDialog
{
	Q_OBJECT

public:
	RegisterDialog(QWidget *parent = 0);
	~RegisterDialog();

	void clearAll();
	void setyanzheng();
	bool judgeEmpty();

private:
	Ui::RegsiterDialog *ui;
	QSqlTableModel *model;
	QButtonGroup *radiogroup;

private slots:
	void registerbtnSlot();
	void  returnbtnSlot();
		
};

#endif // REGSITERDIALOG_H
