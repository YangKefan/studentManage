#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include "ui_logindialog.h"
#include "TeacherManager.h"

class LoginDialog : public QDialog
{
	Q_OBJECT

public:
	LoginDialog(QWidget *parent = 0);
	~LoginDialog();

private:
	Ui::LoginDialog *ui;

private slots:
	void on_loginBtn_clicked(); //²Ûº¯ÊýÉùÃ÷

};

#endif // LOGINDIALOG_H
