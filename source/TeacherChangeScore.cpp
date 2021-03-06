#include "TeacherChangeScore.h"

TeacherChangeScore::TeacherChangeScore(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::TeacherChangeScore)
{
	ui->setupUi(this);
	//设置view列宽适应单元格内容
	ui->teacherchangeview->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

	//判断是否保存
	judge=1;

	//创建model实现与数据库交互
	model=new QSqlTableModel(this);
	model->setTable("student");
	model->setEditStrategy(QSqlTableModel::OnManualSubmit);
	model->setHeaderData(0,Qt::Horizontal,GBK::a2w("学号"));
	model->setHeaderData(1,Qt::Horizontal,GBK::a2w("学生姓名"));
	model->setHeaderData(2,Qt::Horizontal,GBK::a2w("语文成绩"));
	model->setHeaderData(3,Qt::Horizontal,GBK::a2w("数学成绩"));
	model->setHeaderData(4,Qt::Horizontal,GBK::a2w("英语成绩"));
	model->removeColumns(5,5);

	//两个按钮信号和槽函数连接
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
		QMessageBox::information(this,GBK::a2w("提示"),GBK::a2w("学生信息为空，请增加学生信息"),QMessageBox::Yes);
		emit EmitToTeacherManageToChangeStack();
		this->hide();
		return;
	}
	ui->teacherchangeview->setModel(model);
}

void TeacherChangeScore::confirmbtnSlot()
{
	if(model->submitAll())
		QMessageBox::information(this,GBK::a2w("提示"),GBK::a2w("修改成功"),QMessageBox::Yes);
	else
	{
		QMessageBox::information(this,GBK::a2w("提示"),GBK::a2w("修改失败"),QMessageBox::Yes);
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
	if(QMessageBox::question(this,GBK::a2w("提示"),GBK::a2w("尚未保存，是否保存"),QMessageBox::Yes,QMessageBox::No)==QMessageBox::Yes)
	{
		if(model->submitAll())
			QMessageBox::information(this,GBK::a2w("提示"),GBK::a2w("修改成功"),QMessageBox::Yes);
		else
		{
			QMessageBox::information(this,GBK::a2w("提示"),GBK::a2w("修改失败"),QMessageBox::Yes);
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