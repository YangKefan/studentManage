#include "TeacherInsert.h"

TeacherInsert::TeacherInsert(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	// 创建model实现育数据库的交互
	model = new QSqlTableModel();
	model->setTable("student");
	model->setEditStrategy(QSqlTableModel::OnManualSubmit);
	model->removeColumns(5,5);

	connect(ui.returnbtn, SIGNAL(clicked()),this, SLOT(returnBtnSlot()));
	connect(ui.confirmbtn, SIGNAL(clicked()),this, SLOT(confirmBtnSlot()));

}

TeacherInsert::~TeacherInsert()
{

}

void TeacherInsert::clearAll()
{
	ui.nameLine->clear();
	ui.numLine->clear();
	ui.chineseLine->clear();
	ui.mathLine->clear();
	ui.englishLine->clear();
}

bool TeacherInsert::judgeEmpty()
{
	if (ui.numLine->text().isEmpty())
	{
		QMessageBox::warning(this, GBK::a2w("警告"), GBK::a2w("学生学号不能为空"),QMessageBox::Yes);
		return false;
	}
	else if (ui.nameLine->text().isEmpty())
	{
		QMessageBox::warning(this, GBK::a2w("警告"), GBK::a2w("学生姓名不能为空"),QMessageBox::Yes);
		return false;
	}
	else if (ui.chineseLine->text().isEmpty())
	{
		QMessageBox::warning(this, GBK::a2w("警告"), GBK::a2w("学生语文成绩不能为空"),QMessageBox::Yes);
		return false;
	}
	else if (ui.mathLine->text().isEmpty())
	{
		QMessageBox::warning(this, GBK::a2w("警告"), GBK::a2w("学生数学成绩不能为空"),QMessageBox::Yes);
		return false;
	}
	else if (ui.englishLine->text().isEmpty())
	{
		QMessageBox::warning(this, GBK::a2w("警告"), GBK::a2w("学生英语成绩不能为空"),QMessageBox::Yes);
		return false;
	}
	else
	{
		return true;
	}
}

void TeacherInsert::returnBtnSlot()
{
	if(ui.numLine->text().isEmpty()&&ui.nameLine->text().isEmpty()&&
		ui.chineseLine->text().isEmpty()&&ui.mathLine->text().isEmpty()&&
		ui.englishLine->text().isEmpty())
	{
		emit EmitToTeacherManage();
		this->hide();
		return;
	}

	if (QMessageBox::question(this, GBK::a2w("提示"), GBK::a2w("尚未保存，是否退出？"),
		QMessageBox::Yes|QMessageBox::No) == QMessageBox::Yes)
	{
		emit EmitToTeacherManage();
		this->hide();
	}

}

void TeacherInsert::confirmBtnSlot()
{
	if (!this->judgeEmpty()) return;
	
	model->select();
	int i ;
	for (i = 0; i<model->rowCount(); i++)
	{
		// 判断学号是否正确或存在
		if (model->data(model->index(i, 0)).toString() == ui.numLine->text())
		{
			break;
		}
	}

	if ( i != model->rowCount())
	{
		QMessageBox::information(this, GBK::a2w("提示"),GBK::a2w("学生已经存在"), QMessageBox::Yes);
		this->clearAll();
		return;
	}

	QSqlRecord record = model->record();
	record.setValue("studentnum",ui.numLine->text());
	record.setValue("name",ui.nameLine->text());
	record.setValue("chinese",ui.chineseLine->text().toFloat());
	record.setValue("math",ui.mathLine->text().toFloat());
	record.setValue("english",ui.englishLine->text().toFloat());
	model->insertRecord(-1,record);
	if (model->submitAll())
	{
		QMessageBox::information(this,GBK::a2w("提示"),GBK::a2w("学生成绩信息添加成功"),QMessageBox::Yes);
		this->clearAll();
	}

}
