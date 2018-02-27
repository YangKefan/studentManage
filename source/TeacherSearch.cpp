#include "TeacherSearch.h"

TeacherSearch::TeacherSearch(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::TeacherSearch)
{
	ui->setupUi(this);

	// ���ӷ��ذ�ť�ź����
	connect(ui->returnBtn,SIGNAL(clicked()),this,SLOT(returnbtnSlot()));
	connect(ui->searchBtn,SIGNAL(clicked()),this,SLOT(searchbtnSlot()));

	//����view���ɱ༭
	ui->teacherSearchView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui->teacherSearchView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

	// ����model_1ʵ�������ݿ�Ľ���
	model_1 = new QSqlTableModel(this);
	model_1->setTable("student");
	model_1->setEditStrategy(QSqlTableModel::OnManualSubmit); //���ñ������Ϊ�ֶ��ύ
	model_1->setHeaderData(0, Qt::Horizontal, "ѧ��");
	model_1->setHeaderData(1,Qt::Horizontal,"����");
	model_1->setHeaderData(2, Qt::Horizontal,"���ĳɼ�");
	model_1->setHeaderData(3, Qt::Horizontal,"��ѧ�ɼ�");
	model_1->setHeaderData(4, Qt::Horizontal,"Ӣ��ɼ�");
	model_1->removeColumns(5,5);
	
	// ����model_2ʵ�ֲ�ѯ����
	model_2 = new QSqlTableModel(this);
	model_2->setTable("student");
	model_2->setEditStrategy(QSqlTableModel::OnManualSubmit);
	model_2->setHeaderData(0, Qt::Horizontal, "ѧ��");
	model_2->setHeaderData(1,Qt::Horizontal,"����");
	model_2->setHeaderData(2, Qt::Horizontal,"���ĳɼ�");
	model_2->setHeaderData(3, Qt::Horizontal,"��ѧ�ɼ�");
	model_2->setHeaderData(4, Qt::Horizontal,"Ӣ��ɼ�");
	model_2->removeColumns(5,5);

	// ����radiobuttongroup
	radioBtnGroup = new QButtonGroup(this);
	radioBtnGroup->addButton(ui->numRadio, 0);
	radioBtnGroup->addButton(ui->nameRadio,1);

	connect(radioBtnGroup, SIGNAL(clicked()), this, SLOT(radioBtnGroupSlot()) );
	connect(ui->inputLine, SIGNAL(textChanged(QString)), this, SLOT(inputEditSlot(QString)));

}

TeacherSearch::~TeacherSearch()
{
	delete ui;
}

void TeacherSearch::searchBtnSlot()
{
	if (ui->inputLine->text().isEmpty())
	{
		QMessageBox::warning(this, GBK::a2w("����"), GBK::a2w("��ѯ�������Ϊ�գ�"));
		return;
	}
	if (radioBtnGroup->checkedId() == 0)
	{
		//ɸѡ�������ַ���filter�����ݿ����ɸѡ���൱��SQL�е�WHERE���
		model_2->setFilter( "studentNum="+ui->inputLine->text() );
		model_2->select();

		// ѧ��Ϊ�գ����ѧ��������
		if (model_2->data(model_1->index(0,0)).toString().isEmpty())
		{
			QMessageBox::warning(this, GBK::a2w("����"), GBK::a2w("�û������ڣ�") );

			// ������ģ����TableView��
			ui->teacherSearchView->setModel(model_1);
			ui->inputLine->clear();
			return;
		}

		ui->teacherSearchView->setModel(model_2);
	}
	else if(radioBtnGroup->checkedId() == 1 )
	{
		model_2->setFilter("name="+ui->inputLine->text()+"");
		model_2->select();

		// ����Ϊ�գ����ѧ��������
		if ( model_2->data(model_1->index(0,0)).toString().isEmpty() )
		{
			QMessageBox::warning(this, GBK::a2w("����"), GBK::a2w("�û������ڣ�") );

			// ������ģ����TableView��
			ui->teacherSearchView->setModel(model_1);
			ui->inputLine->clear();
			return;
		}
		ui->teacherSearchView->setModel(model_2);
	}
	else
	{
		QMessageBox::warning(this,GBK::a2w("����"), GBK::a2w("��ѡ���ѯ��ʽ��") );
	}
	return;

}// end of searchBtnSlot


void TeacherSearch::comeTeacherManage()
{
	model_1->select();
	if (model_1->data(model_1->index(0,0)).toString().isEmpty())
	{
		QMessageBox::warning(this,GBK::a2w("��ʾ"), GBK::a2w("ѧ����ϢΪ�գ�������ѧ����Ϣ��"),QMessageBox::Yes);
		emit EmitToTeacherManageToChangeStack();
		this->hide();
		return;
	}
	ui->teacherSearchView->setModel(model_1);
	return;

}//end of comeTeacherManage


void TeacherSearch::returnBtnSlot()
{
	ui->inputLine->clear();
	emit EmitToTeacherManage();
	this->hide();
	return;
}


void TeacherSearch::inputEditSlot(QString)
{
	if (ui->inputLine->text().isEmpty())
	{
		ui->teacherSearchView->setModel(model_1);
		
		return;
	}

	return;
}

void TeacherSearch::radioBtnGroupSlot()
{
	ui->teacherSearchView->setModel(model_1);
	ui->inputLine->clear();

	return;
}
