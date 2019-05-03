#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

#define print qDebug()

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mysqlConn_(nullptr)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    if(mysqlConn_ != nullptr){
        mysqlConn_->disconnect();
        delete mysqlConn_;
        mysqlConn_ = nullptr;
        print<<"析构函数断开连接";
    }
    delete ui;
}

void MainWindow::on_pushButtonLink_clicked()
{
    if(mysqlConn_ != nullptr){
        mysqlConn_->disconnect();
        delete mysqlConn_;
        mysqlConn_ = nullptr;
        print<<"断开连接";
        ui->labelState->setText("未连接");
    }
    try{
        mysqlConn_ = new Connection(ui->lineEditDatabase->text().toLatin1(),
                                   ui->lineEditIP->text().toLatin1(),
                                   ui->lineEditUser->text().toLatin1(),
                                   ui->lineEditPassWord->text().toLatin1(),
                                   ui->lineEditPort->text().toInt());
        if(mysqlConn_ != nullptr){
            print<<"连接成功";
            ui->labelState->setText("已连接");
        }else{
            print<<"连接失败";
        }
    }catch(...){
        print<<"连接错误";
    }
}

void MainWindow::on_pushButtonExec_clicked()
{
    if(mysqlConn_ && mysqlConn_->ping()){
        print<<"mysql 执行";
        Query query = mysqlConn_->query(ui->lineEditSql->text().toLatin1());
        StoreQueryResult result = query.store();
        for(auto iter=result.begin();iter!=result.end();++iter){
            Row row = *iter;
            print<<"test"<<QString(row[0]);
        }
        print<<result.size();
    }else{
        print<<"mysql 未连接";
    }
}
