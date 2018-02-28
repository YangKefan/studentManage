#include "TeacherInsert.h"

TeacherInsert::TeacherInsert(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	// ����modelʵ�������ݿ�Ľ���
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
		QMessageBox::warning(this, GBK::a2w("����"), GBK::a2w("ѧ��ѧ�Ų���Ϊ��"),QMessageBox::Yes);
		return false;
	}
	else if (ui.nameLine->text().isEmpty())
	{
		QMessageBox::warning(this, GBK::a2w("����"), GBK::a2w("ѧ����������Ϊ��"),QMessageBox::Yes);
		return false;
	}
	else if (ui.chineseLine->text().isEmpty())
	{
		QMessageBox::warning(this, GBK::a2w("����"), GBK::a2w("ѧ�����ĳɼ�����Ϊ��"),QMessageBox::Yes);
		return false;
	}
	else if (ui.mathLine->text().isEmpty())
	{
		QMessageBox::warning(this, GBK::a2w("����"), GBK::a2w("ѧ����ѧ�ɼ�����Ϊ��"),QMessageBox::Yes);
		return false;
	}
	else if (ui.englishLine->text().isEmpty())
	{
		QMessageBox::warning(this, GBK::a2w("����"), GBK::a2w("ѧ��Ӣ��ɼ�����Ϊ��"),QMessageBox::Yes);
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

	if (QMessageBox::question(this, GBK::a2w("��ʾ"), GBK::a2w("��δ���棬�Ƿ��˳���"),
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
		// �ж�ѧ���Ƿ���ȷ�����
		if (model->data(model->index(i, 0)).toString() == ui.numLine->text())
		{
			break;
		}
	}

	if ( i != model->rowCount())
	{
		QMessageBox::information(this, GBK::a2w("��ʾ"),GBK::a2w("ѧ���Ѿ�����"), QMessageBox::Yes);
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
		QMessageBox::information(this,GBK::a2w("��ʾ"),GBK::a2w("ѧ���ɼ���Ϣ��ӳɹ�"),QMessageBox::Yes);
		this->clearAll();
	}

}
