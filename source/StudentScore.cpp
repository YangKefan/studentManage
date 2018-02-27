#include "StudentScore.h"

StudentScore::StudentScore(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::StudentScore)
{
	ui->setupUi(this);

	// 返回按钮信号与槽连接
	connect(ui->returnBtn, SIGNAL(clicked() ), this, SLOT(returnbtnSlot()));

	// 创建model实现与数据库的连接
	model = new QSqlTableModel(this);
	model->setTable("student");
	model->setEditStrategy(QSqlTableModel::OnManualSubmit);
	model->setHeaderData(0, Qt::Horizontal, "学号");
	model->setHeaderData(1, Qt::Horizontal, "姓名");
	model->setHeaderData(0, Qt::Horizontal, "语文成绩");
	model->setHeaderData(0, Qt::Horizontal, "数学成绩");
	model->setHeaderData(0, Qt::Horizontal, "英语成绩");
	model->removeColumns(5,5);

	// 设置view不可修改
	ui->scoreView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui->scoreView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);	
}

StudentScore::~StudentScore()
{
	delete ui;
}

void StudentScore::comeStudentManage(QString num)
{
	studentnum = num;
	QString str = "studentNum = "+studentnum;
	model->setFilter(str);
	model->select();
	QSqlRecord record = model->record(0);
	if ( record.value(2).toFloat() == 0 &&
		 record.value(3).toFloat() == 0 &&
		  record.value(4).toFloat() == 0 )
	{
		QMessageBox::information(this, GBK::a2w("提示"), GBK::a2w("老师尚未上传成绩,留意班级通知!!"), QMessageBox::Yes);
		//发出信号给StuManage
		emit EmitToStuManage();
		this->hide();
		return;
	}
	ui->scoreView->setModel(model);

}

void StudentScore::returnbtnSlot()
{
	this->hide();
	emit EmitToStuManage();
}
