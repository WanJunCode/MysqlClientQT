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
    mysqlConn_ =new Connection("test_db","localhost", "wanjun", "wanjun", 3306);
    if(mysqlConn_ != nullptr){
        print<<"连接成功";
        ui->labelState->setText("已连接");
    }
}

void MainWindow::on_pushButtonExec_clicked()
{
    if(mysqlConn_ && mysqlConn_->ping()){
        print<<"mysql 执行";

    }else{
        print<<"mysql 未连接";
    }
}
