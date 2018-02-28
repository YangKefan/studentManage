#include "TeacherChangeScore.h"

TeacherChangeScore::TeacherChangeScore(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::TeacherChangeScore)
{
	ui->setupUi(this);
	//����view�п���Ӧ��Ԫ������
	ui->teacherchangeview->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

	//�ж��Ƿ񱣴�
	judge=1;

	//����modelʵ�������ݿ⽻��
	model=new QSqlTableModel(this);
	model->setTable("student");
	model->setEditStrategy(QSqlTableModel::OnManualSubmit);
	model->setHeaderData(0,Qt::Horizontal,GBK::a2w("ѧ��"));
	model->setHeaderData(1,Qt::Horizontal,GBK::a2w("ѧ������"));
	model->setHeaderData(2,Qt::Horizontal,GBK::a2w("���ĳɼ�"));
	model->setHeaderData(3,Qt::Horizontal,GBK::a2w("��ѧ�ɼ�"));
	model->setHeaderData(4,Qt::Horizontal,GBK::a2w("Ӣ��ɼ�"));
	model->removeColumns(5,5);

	//������ť�źźͲۺ�������
	connect(ui->confirmbtn,SIGNAL(clicked()),this,SLOT(confirmbtnSlot()));
	connect(ui->returnbtn,SIGNAL(clicked()),this,SLOT(returnbtnSlot()));
	connect(model,SIGNAL(dataChanged(QModelIndex,QModelIndex)),this,SLOT(judgeSlot(QModelIndex,QModelIndex)));

}

TeacherChangeScore::~TeacherChangeScore()
{
	delete ui;
}

void TeacherChangeScore::comeTeacherManage()
{
	model->select();
	if(model->data(model->index(0,0)).toString().isEmpty())
	{
		QMessageBox::information(this,GBK::a2w("��ʾ"),GBK::a2w("ѧ����ϢΪ�գ�������ѧ����Ϣ"),QMessageBox::Yes);
		emit EmitToTeacherManageToChangeStack();
		this->hide();
		return;
	}
	ui->teacherchangeview->setModel(model);
}

void TeacherChangeScore::confirmbtnSlot()
{
	if(model->submitAll())
		QMessageBox::information(this,GBK::a2w("��ʾ"),GBK::a2w("�޸ĳɹ�"),QMessageBox::Yes);
	else
	{
		QMessageBox::information(this,GBK::a2w("��ʾ"),GBK::a2w("�޸�ʧ��"),QMessageBox::Yes);
		model->revertAll();
	}
	judge=1;
}

void TeacherChangeScore::returnbtnSlot()
{

	if(judge==1)
	{
		emit EmitToTeacherManage();
		this->hide();
		return;
	}
	if(QMessageBox::question(this,GBK::a2w("��ʾ"),GBK::a2w("��δ���棬�Ƿ񱣴�"),QMessageBox::Yes,QMessageBox::No)==QMessageBox::Yes)
	{
		if(model->submitAll())
			QMessageBox::information(this,GBK::a2w("��ʾ"),GBK::a2w("�޸ĳɹ�"),QMessageBox::Yes);
		else
		{
			QMessageBox::information(this,GBK::a2w("��ʾ"),GBK::a2w("�޸�ʧ��"),QMessageBox::Yes);
			model->revertAll();
		}
		emit EmitToTeacherManage();
		this->hide();
		judge=1;
		return ;
	}
	else
	{
		emit EmitToTeacherManage();
		judge=1;
		this->hide();
	}
}

void TeacherChangeScore::judgeSlot(QModelIndex, QModelIndex)
{
	judge=0;
}