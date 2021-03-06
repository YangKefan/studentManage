#include "TeacherSearch.h"

TeacherSearch::TeacherSearch(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::TeacherSearch)
{
	ui->setupUi(this);

	// 创建model_1实现与数据库的交互
	model_1 = new QSqlTableModel(this);
	model_1->setTable("student");	
	model_1->setEditStrategy(QSqlTableModel::OnManualSubmit); //设置保存策略为手动提交
	model_1->setHeaderData(0, Qt::Horizontal, GBK::a2w("学号"));
	model_1->setHeaderData(1,Qt::Horizontal,GBK::a2w("姓名"));
	model_1->setHeaderData(2, Qt::Horizontal,GBK::a2w("语文成绩"));
	model_1->setHeaderData(3, Qt::Horizontal,GBK::a2w("数学成绩"));
	model_1->setHeaderData(4, Qt::Horizontal,GBK::a2w("英语成绩"));
		
	
	// 创建model_2实现查询功能
	model_2 = new QSqlTableModel(this);
	model_2->setTable("student");
	model_2->setEditStrategy(QSqlTableModel::OnManualSubmit);
	model_2->setHeaderData(0, Qt::Horizontal, GBK::a2w("学号"));
	model_2->setHeaderData(1,Qt::Horizontal,GBK::a2w("姓名"));
	model_2->setHeaderData(2, Qt::Horizontal,GBK::a2w("语文成绩"));
	model_2->setHeaderData(3, Qt::Horizontal,GBK::a2w("数学成绩"));
	model_2->setHeaderData(4, Qt::Horizontal,GBK::a2w("英语成绩"));

	// 创建radiobuttongroup
	radioBtnGroup = new QButtonGroup();
	radioBtnGroup->addButton(ui->numRadio, 0);
	radioBtnGroup->addButton(ui->nameRadio,1);

	connect(radioBtnGroup, SIGNAL(clicked()), this, SLOT(radioBtnGroupSlot(int)) );
	connect(ui->inputLine, SIGNAL(textChanged(QString)), this, SLOT(inputEditSlot(QString)));

	// 连接返回按钮信号与槽
	connect(ui->returnBtn,SIGNAL(clicked()),this,SLOT(returnbtnSlot()));
	connect(ui->searchBtn,SIGNAL(clicked()),this,SLOT(searchbtnSlot()));
}

TeacherSearch::~TeacherSearch()
{
	delete ui;
}

void TeacherSearch::searchBtnSlot()
{
	if (ui->inputLine->text().isEmpty())
	{
		QMessageBox::warning(this, GBK::a2w("警告"), GBK::a2w("查询输入框不能为空！"));
		return;
	}
	if (radioBtnGroup->checkedId() == 0)
	{
		//筛选，按照字符串filter对数据库进行筛选，相当于SQL中的WHERE语句
		model_2->setFilter( "studentNum="+ui->inputLine->text() );
		model_2->select();

		// 学号为空，则此学生不存在
		if (model_2->data(model_1->index(0,0)).toString().isEmpty())
		{
			QMessageBox::warning(this, GBK::a2w("警告"), GBK::a2w("用户不存在！") );

			// 将数据模型与TableView绑定
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

		// 姓名为空，则此学生不存在
		if ( model_2->data(model_1->index(0,0)).toString().isEmpty() )
		{
			QMessageBox::warning(this, GBK::a2w("警告"), GBK::a2w("用户不存在！") );

			// 将数据模型与TableView绑定
			ui->teacherSearchView->setModel(model_1);
			ui->inputLine->clear();
			return;
		}
		ui->teacherSearchView->setModel(model_2);
	}
	else
	{
		QMessageBox::warning(this,GBK::a2w("警告"), GBK::a2w("请选择查询方式！") );
	}
	return;

}// end of searchBtnSlot


void TeacherSearch::comeTeacherManage()
{
	model_1->select();
	qDebug()<<model_1->data(model_1->index(0,0));
	if (model_1->data(model_1->index(0,0)).toString().isEmpty())
	{
		QMessageBox::warning(this,GBK::a2w("提示"), GBK::a2w("学生信息为空，请增加学生信息！"),QMessageBox::Yes);
		emit EmitToTeacherManageToChangeStack();
		this->hide();
		return;
	}

	// 利用setModel()方法将数据模型与QTableView绑定
	ui->teacherSearchView->setModel(model_1);

	// 设置选中时为整行选中 
	ui->teacherSearchView->setSelectionBehavior(QAbstractItemView::SelectRows);

	// 设置选中单个目标
	ui->teacherSearchView->setSelectionMode(QAbstractItemView::SingleSelection);

	// 设置每列宽度适中
	ui->teacherSearchView->resizeColumnsToContents();

	// 设置表头均分填充容器
	ui->teacherSearchView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

	// 隐藏不显示的列
	ui->teacherSearchView->setColumnHidden(5,true);
	ui->teacherSearchView->setColumnHidden(6,true);
	ui->teacherSearchView->setColumnHidden(7,true);
	ui->teacherSearchView->setColumnHidden(8,true);

	//表头qss设置
	QString strHeaderQss;
	strHeaderQss = "QHeaderView::section { background:green; color:white;min-height:3em;}";
	ui->teacherSearchView->setStyleSheet(strHeaderQss);
	
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
		QMessageBox::warning(this, GBK::a2w("警告"), GBK::a2w("查询输入框不能为空！") );
		ui->teacherSearchView->setModel(model_1);		
		return;
	}
	return;
}

void TeacherSearch::radioBtnGroupSlot(int)
{
	ui->teacherSearchView->setModel(model_2);
	ui->inputLine->clear();

	return;
}
