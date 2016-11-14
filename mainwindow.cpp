#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include "specialworker.h"

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
    qDebug() << "MainWindow::calcFunc";
    for(long long i=1; i<10;++i)
    {
        I::sleep(1);
        static long long j = 1;
        j+=qrand()%10;
        array.append(j);
        qDebug()<<j;

        setProc(i*10);
    }
}

void doCalc()
{
    QList<long long> array;
    qDebug() << "doCalc";
    for(long long i=1; i<5;++i)
    {
        I::sleep(1);
        static long long j = 1;
        j+=qrand()%10;
        array.append(j);
        qDebug()<<j;
    }
}

void MainWindow::on_pushButton_clicked()
{
#define CASE 3
#if CASE == 1
    // CASE 1
    LoadingDialog *dlg = new LoadingDialog(this);
    dlg->setFunc(&doCalc);
    dlg->run();
#elif CASE == 2
//    // CASE 2
    LoadingDialog *dlg = new LoadingDialog(this);
    dlg->setDefiniteMode();
    dlg->setProcessName(QString::fromUtf8("Тестовое приложение"));
    SpecialWorker *worker = new SpecialWorker();
    worker->setMainWindow(this);
    dlg->setWorker(worker);
    dlg->run();
#elif CASE == 3
    LoadingDialog *dlg = new LoadingDialog(this);
    dlg->setUnlimittedMode();
    dlg->setProcessName(QString::fromUtf8("Тестовое приложение"));
    dlg->show();
#endif
}

void JustTest::calcFunc()
{
    qDebug() <<"JustTest calcFunc";
    qDebug() << "current Thread is " << thread();
    qDebug() << "main thread is "<< QApplication::instance()->thread();
    QList<long long> array;
    //    qDebug() << "Count = "<<count;
    for(long long i=1; i<1000000;++i)
    {
        static long long j = 1;
        j+=qrand()%10;
        array.append(j);
        qDebug()<<j;
    }
}
