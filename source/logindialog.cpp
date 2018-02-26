#include "logindialog.h"

LoginDialog::LoginDialog(QWidget *parent)
	: QDialog(parent)
{
	ui->setupUi(this);
}

LoginDialog::~LoginDialog()
{

}

void LoginDialog::on_loginBtn_clicked()
{
	if(ui->userlineEdit->text() == tr("caddress")&&ui->passwordLineEdit->text()==tr("123456"))
		accept();
	else{
		QMessageBox::warning(this,tr("Warning"),tr("user name or password error!"),QMessageBox::Yes);
	}
}
