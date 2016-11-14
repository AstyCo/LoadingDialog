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

void MainWindow::calcFunc()
{
    QList<long long> array;
    for(long long i=1; i<1000000;++i)
    {
//        I::sleep(1);
        static long long j = 1;
        j+=qrand()%10;
        array.append(j);
        qDebug()<<j;
    }
}

void MainWindow::on_pushButton_clicked()
{
    LoadingDialog *dlg = new LoadingDialog(this);
    dlg->show();
    //QApplication::processEvents();
    calcFunc();
//    dlg->close();
}
