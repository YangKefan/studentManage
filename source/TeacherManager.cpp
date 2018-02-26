#include "TeacherManager.h"

TeacherManager::TeacherManager(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::TeacherManager)
{
	ui->setupUi(this);
}

TeacherManager::~TeacherManager()
{
	delete ui;
}
void TeacherManager::setbtnfalse()
{
	ui->searchbtn->setEnabled(false);
	ui->changebtn->setEnabled(false);
	ui->insertbtn->setEnabled(false);
	ui->deletebtn->setEnabled(false);
	ui->passwordbtn->setEnabled(false);
	ui->returnbtn->setEnabled(false);
	ui->exitbtn->setEnabled(false);
}
void TeacherManager::setbtntrue()
{
	ui->searchbtn->setEnabled(true);
	ui->changebtn->setEnabled(true);
	ui->insertbtn->setEnabled(true);
	ui->deletebtn->setEnabled(true);
	ui->passwordbtn->setEnabled(true);
	ui->returnbtn->setEnabled(true);
	ui->exitbtn->setEnabled(true);
}

void TeacherManager::searchbtnSlot()
{
	this->setbtnfalse();
	teachersearch->show();
	
	emit toTeacherSearch();
}

void TeacherManager::exitbtnSlot()
{
	if(QMessageBox::question(this,GBK::a2w("提示"),GBK::a2w("是否退出系统?"),QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
	{
		this->close();
		delete this;
	}
}