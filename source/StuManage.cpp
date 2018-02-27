#include "StuManage.h"

StuManage::StuManage(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::StuManage)
{
	ui->setupUi(this);
	//����ѧ���ɼ���ѯ����
	studentscore=new StudentScore(this);
	ui->sudentstack->addWidget(studentscore);
	connect(ui->scorebtn,SIGNAL(clicked()),this,SLOT(scorebtnSlot()));
	connect(this,SIGNAL(toStudentScore(QString)),studentscore,SLOT(comeStudentManage(QString)));

	//�˳�ϵͳ��ť�ź��������
	connect(ui->exitbtn,SIGNAL(clicked()),this,SLOT(exitbtnSlot()));
}

StuManage::~StuManage()
{

}

void StuManage::btnsetfalse()
{
	ui->passwordbtn->setEnabled(false);
	ui->searchbtn->setEnabled(false);
	ui->exitbtn->setEnabled(false);
	ui->scorebtn->setEnabled(false);
	ui->infobtn->setEnabled(false);
	ui->returnbtn->setEnabled(false);
}

void StuManage::btnsettrue()
{
	ui->exitbtn->setEnabled(true);
	ui->infobtn->setEnabled(true);
	ui->searchbtn->setEnabled(true);
	ui->passwordbtn->setEnabled(true);
	ui->scorebtn->setEnabled(true);
	ui->returnbtn->setEnabled(true);
}

void StuManage::comeLoginDialogSlot(QString name,QString num)
{
	studentname = name;
	studentnum = num;
	ui->studentnameline->setText(studentname);
}

 void StuManage::exitbtnSlot()
 {
	 if (QMessageBox::question(this, GBK::a2w("��ʾ"),GBK::a2w("�Ƿ��˳�ϵͳ��"), 
		 QMessageBox::Yes|QMessageBox::No) == QMessageBox::Yes)
	 {
		 this->close();
		 delete this;
	 }

 }

 void StuManage::scorebtnSlot()
 {
	 studentscore->show();
	 ui->sudentstack->setCurrentIndex(3);
	 this->btnsetfalse();
	 emit toStudentScore(studentnum);
 }

 void StuManage::setbtnEnable()
 {
	 this->btnsettrue();
 }