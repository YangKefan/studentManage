#include "RegisterDialog.h"
#include "GBK.h"

RegisterDialog::RegisterDialog(QWidget *parent)
	: QDialog(parent),
	ui(new Ui::RegsiterDialog)
{
	ui->setupUi(this);
	//ui->setFixedSize(500,600);

	//����model,�������ݿ����
	model=new QSqlTableModel(this);
	model->setEditStrategy(QSqlTableModel::OnManualSubmit);

	//����QButtonGroup
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
		QMessageBox::warning(this,GBK::a2w("����"),GBK::a2w("�û�������Ϊ��"));
		return false;
	}
	else if(ui->accountEdit->text().isEmpty())
	{
		QMessageBox::warning(this,GBK::a2w("����"),GBK::a2w("�û������Ų���Ϊ��"));
		return false;
	}
	else if(ui->passwordEdit->text().isEmpty()||
		ui->passwordEdit_2->text().isEmpty())
	{
		QMessageBox::warning(this,GBK::a2w("����"),GBK::a2w("�û����벻��Ϊ��"));
		return false;
	}	
	else
		return true;
}


void RegisterDialog::registerbtnSlot()
{
	int i;
	//�ж�lineedit�Ƿ�Ϊ��
	if(!this->judgeEmpty())
	{				
		return;
	}
	//�ж��������������Ƿ�һ��
	if(ui->passwordEdit->text()!=ui->passwordEdit_2->text())
	{
		QMessageBox::warning(this,GBK::a2w("����"),GBK::a2w("�����������벻һ��"),QMessageBox::Yes);
		ui->passwordEdit->clear();
		ui->passwordEdit->clear();		
		return;
	}
	
	//�ж��Ƿ�ѧ��ע��
	if(radiogroup->checkedId()==0)
	{
		//����tableΪstudent��
		model->setTable("student");
		model->select();
		for(i=0;i<model->rowCount();i++)
		{
			QSqlRecord record=model->record(i);
			//�ж�ѧ����Ϣ�Ѿ�����
			if((record.value(0)==ui->accountEdit->text()&&record.value(5)!=""))
			{
				QMessageBox::warning(this,GBK::a2w("����"),GBK::a2w("�û��Ѵ���"),QMessageBox::Yes);
				this->clearAll();
				this->setyanzheng();
				return;
			}
		}
		//���ѧ����Ϣ������,���ѧ����Ϣ�����ݿ�
		if(i==model->rowCount())
		{
			QSqlRecord record1=model->record();
			record1.setValue("studentNum",ui->accountEdit->text());
			record1.setValue("name",ui->userEdit->text());
			record1.setValue("password",ui->passwordEdit->text());
			model->insertRecord(-1,record1);
		}
		//�ж�ѧ����Ϣ�Ƿ��ϴ����ݿ�ɹ�
		if(model->submitAll())
		{
			QMessageBox::information(this,GBK::a2w("��ʾ"),GBK::a2w("��ϲ��ע��ɹ�^*^"),QMessageBox::Yes);
			this->accept();
		}
		//�ϴ����ɹ�
		else
		{
			QMessageBox::information(this,GBK::a2w("��ʾ"),GBK::a2w("ע��ʧ��������ע��"),QMessageBox::Yes);
		}
			
		this->clearAll();
		this->setyanzheng();
	}

	//�ж��Ƿ���ʦע��
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
				QMessageBox::warning(this,GBK::a2w("����"),GBK::a2w("�û��Ѵ���"),QMessageBox::Yes);
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
		//�жϽ�ʦ��Ϣ�Ƿ��ϴ����ݿ�ɹ�
		if(model->submitAll())
		{
			QMessageBox::information(this,GBK::a2w("��ʾ"),GBK::a2w("��ϲ��ע��ɹ�^*^"),QMessageBox::Yes);
			this->accept();
		}
		//�ϴ����ɹ�
		else
		{
			QMessageBox::information(this,GBK::a2w("��ʾ"),GBK::a2w("ע��ʧ��������ע��"),QMessageBox::Yes);
		}
			
		this->clearAll();
		this->setyanzheng();
	}
	else
	{
		QMessageBox::warning(this,GBK::a2w("����"),GBK::a2w("��ѡ��ע�᷽ʽ"),QMessageBox::Yes);
	}
	
}

void RegisterDialog::returnbtnSlot()
{
	this->accept();
}