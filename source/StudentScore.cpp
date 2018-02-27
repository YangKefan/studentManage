#include "StudentScore.h"

StudentScore::StudentScore(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::StudentScore)
{
	ui->setupUi(this);

	// ���ذ�ť�ź��������
	connect(ui->returnBtn, SIGNAL(clicked() ), this, SLOT(returnbtnSlot()));

	// ����modelʵ�������ݿ������
	model = new QSqlTableModel(this);
	model->setTable("student");
	model->setEditStrategy(QSqlTableModel::OnManualSubmit);
	model->setHeaderData(0, Qt::Horizontal, "ѧ��");
	model->setHeaderData(1, Qt::Horizontal, "����");
	model->setHeaderData(0, Qt::Horizontal, "���ĳɼ�");
	model->setHeaderData(0, Qt::Horizontal, "��ѧ�ɼ�");
	model->setHeaderData(0, Qt::Horizontal, "Ӣ��ɼ�");
	model->removeColumns(5,5);

	// ����view�����޸�
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
		QMessageBox::information(this, GBK::a2w("��ʾ"), GBK::a2w("��ʦ��δ�ϴ��ɼ�,����༶֪ͨ!!"), QMessageBox::Yes);
		//�����źŸ�StuManage
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
