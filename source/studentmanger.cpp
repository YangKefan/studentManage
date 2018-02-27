#include "studentmanger.h"
#include "RegisterDialog.h"
#include "GBK.h"

#include <QMessageBox>
#include <QPushButton>
#include <QDialog>
#include <QtSql/QSqlDatabase>
#include <QDebug>

StudentManger::StudentManger(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::StudentMangerClass)
{
	ui->setupUi(this);	

	QString dataname = "school.db";
	connectSqlite(dataname);

	//创建QSqlTableModel
	model=new QSqlTableModel(this);
	model->setEditStrategy(QSqlTableModel::OnManualSubmit);

	// 对radiobutton编号
	radiogroup = new QButtonGroup(this);
	radiogroup->addButton(ui->teacherRadio, 1);
	radiogroup->addButton(ui->studentRadio, 0);
	
	connect(ui->loginBtn, SIGNAL(clicked()), this, SLOT(on_loginButton_clicked() ) );
	connect(ui->exitBtn, SIGNAL(clicked()),this, SLOT(on_exitButton_clicked() ) );
	connect(ui->registerBth, SIGNAL(clicked()), this, SLOT(on_registerButton_clicked() ) );
}

StudentManger::~StudentManger()
{
	delete ui;
}

bool StudentManger::connectSqlite(QString &dataName)
{
	// 设置数据库驱动
	QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
	database.setDatabaseName(dataName);
	if (!database.open())
	{
		qDebug()<<"DataBase Error !";
		return false;
	}
	else
	{
		qDebug()<<"connect dataBase successfully !";
	}
	return true;
}

void StudentManger::clearAll()
{
	ui->userLine->clear();
	ui->passwordLine->clear();
	return;
}

bool StudentManger::judgeEmpty()
{
	if(ui->userLine->text().isEmpty())
	{
		QMessageBox::warning(this,GBK::a2w("警告"),GBK::a2w("用户名不能为空"));
		return false;
	}
	if(ui->passwordLine->text().isEmpty())
	{
		QMessageBox::warning(this,GBK::a2w("警告"),GBK::a2w("密码不能为空"));
		return false;
	}

	return true;
		
}

void StudentManger::on_loginButton_clicked()
{

	if(!this->judgeEmpty())
	{
		ui->passwordLine->clear();
		return;
	}

	//判断是否学生登录
	if(radiogroup->checkedId()==0)
	{
		model->setTable("student");
		model->select();
		qDebug()<<model->rowCount();
		int i;
		for(i=0;i<model->rowCount();i++)
		{
			QSqlRecord record=model->record(i);

			//qDebug()<<record.value(0)<<record.value(6);

			if(record.value(0)==ui->userLine->text()&&
				record.value(6)==ui->passwordLine->text())
			{
				QString str1=GBK::a2w("登录成功");
				QString str2=record.value(1).toString();
				QString str3=GBK::a2w("学生");
				QMessageBox::information(this,GBK::a2w("提示"),str3+str2+str1,QMessageBox::Yes);
				this->clearAll();
				////创建学生成绩管理窗口
				//student=new StudentManage;
				////连接学生成绩管理窗口和登录对话框信号与槽
				//connect(student,SIGNAL(toLoginDialog()),this,SLOT(showNormal()));
				//student->show();
				//connect(this,SIGNAL(toStudentManage(QString,QString)),student,SLOT(comeLoginDialog(QString,QString)));
				//emit toStudentManage(str2,record.value(0).toString());
				//this->hide();
				return;
			}
			else if(record.value(0)==ui->userLine->text()&&
				record.value(6)!=ui->passwordLine->text())
			{
				QMessageBox::information(this,GBK::a2w("提示"),GBK::a2w("密码输入有误"),QMessageBox::Yes);
				this->clearAll();
				return;
			}
		}
		QMessageBox::warning(this,GBK::a2w("提示"),GBK::a2w("用户不存在,请注册"),QMessageBox::Yes);
		this->clearAll();
		return;
	}
	else if(radiogroup->checkedId()==1)
	{
		model->setTable("teacher");
		model->select();
		int i;		
		for(i=0;i<model->rowCount();i++)
		{
			QSqlRecord record=model->record(i);
			qDebug()<<record.value(0)<<record.value(6);

			if(record.value(0)==ui->userLine->text()&&
				record.value(2)==ui->passwordLine->text())
			{
				QString str1=GBK::a2w("登录成功");
				QString str2=record.value(1).toString();
				QString str3=GBK::a2w("教师");
				QMessageBox::information(this,GBK::a2w("提示"),str3+str2+str1,QMessageBox::Yes);
				//创建教师成绩管理窗口
				teacher=new TeacherManager;
				teacher->show();
				emit toTeacherManage(str2,record.value(0).toString());
				connect(this,SIGNAL(toTeacherManage(QString,QString)),teacher,SLOT(comeLoginDialog(QString,QString)));
				connect(teacher,SIGNAL(toLoginDialog()),this,SLOT(showNormal()));
				
				this->clearAll();
				this->hide();
				return;
			}
			else if(record.value(0)==ui->userLine->text()&&
				record.value(2)!=ui->passwordLine->text())
			{
				QMessageBox::information(this,"提示","密码输入有误",QMessageBox::Yes);
				this->clearAll();
				return;
			}
		}
		QMessageBox::warning(this,GBK::a2w("提示"),GBK::a2w("用户不存在,请注册"),QMessageBox::Yes);
		this->clearAll();
		return;
	}
	else
	{
		QMessageBox::warning(this,GBK::a2w("警告"),GBK::a2w("请选择登录方式"),QMessageBox::Yes);
	}
		

	//if (this->ui->userLine->text().trimmed() == tr("Manuel") && 
	//	this->ui->passwordLine->text().trimmed() == tr("123456789"))
	//{
	//	// 登录成功后显示对话框
	//	QDialog *dialogLogin = new QDialog;
	//	dialogLogin->show();
	//}
	//else
	//{
	//	// 用户输入存在错误
	//	QMessageBox::warning(this, tr("warning"), tr("your password is wrong"), QMessageBox::Yes );
	//	ui->userLine->clear();
	//	ui->passwordLine->clear();
	//	ui->userLine->setFocus();//将鼠标重新定位到userLine
	//}

}

void StudentManger::on_exitButton_clicked()
{
	this->close();
}

void StudentManger::on_registerButton_clicked()
{
	// 注册
	RegisterDialog *dialogLogin = new RegisterDialog;
	dialogLogin->show();
	dialogLogin->exec();
}