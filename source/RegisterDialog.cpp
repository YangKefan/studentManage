#include "RegisterDialog.h"
#include "GBK.h"

RegisterDialog::RegisterDialog(QWidget *parent)
	: QDialog(parent),
	ui(new Ui::RegsiterDialog)
{
	ui->setupUi(this);
	//ui->setFixedSize(500,600);

	//创建model,进行数据库操作
	model=new QSqlTableModel(this);
	model->setEditStrategy(QSqlTableModel::OnManualSubmit);

	//设置QButtonGroup
	radiogroup=new QButtonGroup(this);
	radiogroup->addButton(ui->studentBtn,0);
	radiogroup->addButton(ui->teacherBtn,1);

	connect(ui->regBtn, SIGNAL(clicked()), this, SLOT(registerbtnSlot()) );
	connect(ui->backBtn, SIGNAL(clicked()), this, SLOT(returnbtnSlot()) );
}

RegisterDialog::~RegisterDialog()
{
	 delete ui;
}

void RegisterDialog::clearAll()
{
	ui->userEdit->clear();
	ui->accountEdit->clear();
	ui->passwordEdit->clear();
	ui->passwordEdit_2->clear();

	return;
}

void RegisterDialog::setyanzheng()
{

}
bool RegisterDialog::judgeEmpty()
{
	if(ui->userEdit->text().isEmpty())
	{
		QMessageBox::warning(this,GBK::a2w("警告"),GBK::a2w("用户名不能为空"));
		return false;
	}
	else if(ui->accountEdit->text().isEmpty())
	{
		QMessageBox::warning(this,GBK::a2w("警告"),GBK::a2w("用户工作号不能为空"));
		return false;
	}
	else if(ui->passwordEdit->text().isEmpty()||
		ui->passwordEdit_2->text().isEmpty())
	{
		QMessageBox::warning(this,GBK::a2w("警告"),GBK::a2w("用户密码不能为空"));
		return false;
	}	
	else
		return true;
}


void RegisterDialog::registerbtnSlot()
{
	int i;
	//判断lineedit是否为空
	if(!this->judgeEmpty())
	{				
		return;
	}
	//判断两次密码输入是否一致
	if(ui->passwordEdit->text()!=ui->passwordEdit_2->text())
	{
		QMessageBox::warning(this,GBK::a2w("警告"),GBK::a2w("两次密码输入不一致"),QMessageBox::Yes);
		ui->passwordEdit->clear();
		ui->passwordEdit->clear();		
		return;
	}
	
	//判断是否学生注册
	if(radiogroup->checkedId()==0)
	{
		//设置table为student表
		model->setTable("student");
		model->select();
		for(i=0;i<model->rowCount();i++)
		{
			QSqlRecord record=model->record(i);
			//判断学生信息已经存在
			if((record.value(0)==ui->accountEdit->text()&&record.value(5)!=""))
			{
				QMessageBox::warning(this,GBK::a2w("警告"),GBK::a2w("用户已存在"),QMessageBox::Yes);
				this->clearAll();
				this->setyanzheng();
				return;
			}
		}
		//如果学生信息不存在,添加学生信息进数据库
		if(i==model->rowCount())
		{
			QSqlRecord record1=model->record();
			record1.setValue("studentNum",ui->accountEdit->text());
			record1.setValue("name",ui->userEdit->text());
			record1.setValue("password",ui->passwordEdit->text());
			model->insertRecord(-1,record1);
		}
		//判断学生信息是否上传数据库成功
		if(model->submitAll())
		{
			QMessageBox::information(this,GBK::a2w("提示"),GBK::a2w("恭喜你注册成功^*^"),QMessageBox::Yes);
			this->accept();
		}
		//上传不成功
		else
		{
			QMessageBox::information(this,GBK::a2w("提示"),GBK::a2w("注册失败请重新注册"),QMessageBox::Yes);
		}
			
		this->clearAll();
		this->setyanzheng();
	}

	//判断是否老师注册
	else if(radiogroup->checkedId()==1)
	{
		int i;
		model->setTable("teacher");
		model->select();
		for(i=0;i<model->rowCount();i++)
		{
			QSqlRecord record=model->record(i);
			if(record.value(0)==ui->accountEdit->text())
			{
				QMessageBox::warning(this,GBK::a2w("警告"),GBK::a2w("用户已存在"),QMessageBox::Yes);
				this->clearAll();
				this->setyanzheng();
				return;
			}
		}
		if(i==model->rowCount())
		{
			QSqlRecord record=model->record();
			record.setValue("teacherNum",ui->accountEdit->text());
			record.setValue("name",ui->userEdit->text());
			record.setValue("password",ui->passwordEdit->text());
			model->insertRecord(-1,record);
		}
		//判断教师信息是否上传数据库成功
		if(model->submitAll())
		{
			QMessageBox::information(this,GBK::a2w("提示"),GBK::a2w("恭喜你注册成功^*^"),QMessageBox::Yes);
			this->accept();
		}
		//上传不成功
		else
		{
			QMessageBox::information(this,GBK::a2w("提示"),GBK::a2w("注册失败请重新注册"),QMessageBox::Yes);
		}
			
		this->clearAll();
		this->setyanzheng();
	}
	else
	{
		QMessageBox::warning(this,GBK::a2w("警告"),GBK::a2w("请选择注册方式"),QMessageBox::Yes);
	}
	
}

void RegisterDialog::returnbtnSlot()
{
	this->accept();
}