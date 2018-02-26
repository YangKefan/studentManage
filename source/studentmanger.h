#ifndef STUDENTMANGER_H
#define STUDENTMANGER_H

#include "ui_studentmanger.h"
#include "TeacherManager.h"

#include <QtWidgets/QMainWindow>
#include <QDialog>
#include <QButtonGroup>
#include <QSqlTableModel>
#include <QSqlRecord>

class StudentManger : public QMainWindow
{
	Q_OBJECT

public:
	explicit StudentManger(QWidget *parent = 0);
	~StudentManger();

	bool connectSqlite(QString &dataName);
	void clearAll();
	bool judgeEmpty();

private:
	Ui::StudentMangerClass *ui;
	QButtonGroup *radiogroup;
	QSqlTableModel *model;
	TeacherManager *teacher;

private slots:
	void on_loginButton_clicked(); // µÇÂ¼²Û
	void on_exitButton_clicked(); // ÍË³ö²Û
	void on_registerButton_clicked(); // ×¢²á²Û

signals:
	void toStudentManage(QString,QString);
	void toTeacherManage(QString,QString);

};

#endif // STUDENTMANGER_H
