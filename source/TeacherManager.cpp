#include "TeacherManager.h"

TeacherManager::TeacherManager(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::TeacherManager)
{
	ui->setupUi(this);
	
	// 连接退出系统按钮信号与槽
	connect(ui->exitbtn, SIGNAL(clicked()), this, SLOT(exitbtnSlot()));

	// 创建教师成绩查询窗口
	teachersearch = new TeacherSearch(this);
	ui->teacherstack->addWidget(teachersearch);
	connect(this, SIGNAL(toTeacherSearch()), teachersearch, SLOT(comeTeacherManage()));
	connect(ui->searchbtn, SIGNAL(clicked()), this, SLOT(searchbtnSlot()));
	
	//实现多个功能窗口与教师管理窗口信号槽连接，用于设置button属性
	connect(teachersearch, SIGNAL(EmitToTeacherManage()), this, SLOT(setbtnEnableSlot()));
	connect(teachersearch,SIGNAL(EmitToTeacherManageToChangeStack()),this,SLOT(tosetStack()));
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

void TeacherManager::comeLoginDialog(QString name, QString num)
{
	teachername=name;
	teachernum=num;
	ui->teachernameline->setText(teachername);
}

void TeacherManager::setbtnEnableSlot()
{
	this->setbtntrue();
}

 void TeacherManager::tosetStack()
 {

 }