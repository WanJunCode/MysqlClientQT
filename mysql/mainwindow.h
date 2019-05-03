#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#define MYSQLPP_MYSQL_HEADERS_BURIED
#include <mysql++/mysql++.h>

namespace Ui {
class MainWindow;
}

using namespace mysqlpp;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButtonLink_clicked();

    void on_pushButtonExec_clicked();

private:
    Ui::MainWindow *ui;
    Connection *mysqlConn_;
};

#endif // MAINWINDOW_H
