#include "loadingdialog.h"
#include "ui_loadingdialog.h"

#include <QDebug>
#include <QTime>
#include <QKeyEvent>
#include <QThread>
#include "worker.h"




LoadingDialog::LoadingDialog(QWidget *parent) :
    QDialog(parent,Qt::Window |  Qt::FramelessWindowHint),
    ui(new Ui::LoadingDialog)
{
    ui->setupUi(this);
    init();
    setAttribute(Qt::WA_NoSystemBackground, true);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setWindowModality(Qt::ApplicationModal);

}

LoadingDialog::~LoadingDialog()
{
    delete ui;
}

void LoadingDialog::setFunc(void (*f)())
{
    m_func = f;
    if(m_worker)
        m_worker->setFunc(f);
}

void LoadingDialog::run()
{
//    if(m_func == NULL)
//    {
//        qWarning("LoadingDialog:: m_func is NULL, call setFunc() before run()");
//        return;
//    }

    QThread *t = new QThread();
    if(m_worker==NULL)
    {
        m_worker = new Worker();
        m_worker->setFunc(m_func);
    }
    connect(m_worker,SIGNAL(setProc(int)),this,SLOT(setProc(int)));

    m_worker->moveToThread(t);
    connect( t, SIGNAL(started()), m_worker, SLOT(doWork()) );
    connect( m_worker, SIGNAL(workFinished()), t, SLOT(quit()) );

    //automatically delete thread and task object when work is done:
    connect( t, SIGNAL(finished()), m_worker, SLOT(deleteLater()) );
    connect( t, SIGNAL(finished()), t, SLOT(deleteLater()) );
    connect( t, SIGNAL(finished()), this, SLOT(onThreadFinished()) );

    t->start();

    show();

    // sync. wait till thread finished
    cycle();

    close();
}

void LoadingDialog::init()
{
    m_func = NULL;
    m_worker = NULL;
    _threadFinished=false;

    initSpinner();
}

void LoadingDialog::initSpinner()
{
    ui->spinner->setRoundness(70.0);
    ui->spinner->setMinimumTrailOpacity(15.0);
    ui->spinner->setTrailFadePercentage(70.0);
    ui->spinner->setNumberOfLines(12);
    ui->spinner->setLineLength(10);
    ui->spinner->setLineWidth(5);
    ui->spinner->setInnerRadius(10);
    ui->spinner->setRevolutionsPerSecond(1);

    ui->spinner->start(); // gets the show on the road!


}

void LoadingDialog::cycle()
{
    for(;;)
    {
        if(_threadFinished)
            break;

        QApplication::processEvents();
    }
}

void LoadingDialog::onThreadFinished()
{
    _threadFinished=true;
}

void LoadingDialog::setWorker(Worker *worker)
{
    m_worker = worker;
}

void LoadingDialog::setUnlimittedMode()
{
    ui->spinner->setMode(WaitingSpinnerWidget::UnlimittedMode);
}

void LoadingDialog::setDefiniteMode()
{
    ui->spinner->setMode(WaitingSpinnerWidget::DefiniteMode);
}

void LoadingDialog::setProc(int proc)
{
    ui->spinner->setProc(proc);
//    ui->labelWait->setText(QString::fromUtf8("Подождите... ")+QString::number(proc)+'%');
}

void LoadingDialog::setProcessName(const QString &str)
{
//    ui->spinner->setProcessName(str);
    ui->labelProcessName->setText(str);
}
