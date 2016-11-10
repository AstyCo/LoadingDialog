#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


//    calcFactorial();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::calcFactorial()
{
    QList<long long> factorialArray;
    for(int i=1; i<100;++i)
    {
        static long long j = 1;
        j*=i;
        factorialArray.append(j);
        qDebug()<<j;
    }
}

void MainWindow::on_pushButton_clicked()
{
    LoadingDialog *dlg = new LoadingDialog(this);
    dlg->exec();
}
