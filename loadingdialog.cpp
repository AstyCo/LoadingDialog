#include "loadingdialog.h"
#include "ui_loadingdialog.h"

#include <QDebug>
#include <QTime>
#include <QKeyEvent>
#include <QThread>
#include "worker.h"




LoadingDialog::LoadingDialog(Worker *worker, QWidget *parent)
{
    init();

    setWorker(worker);
}

LoadingDialog::LoadingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoadingDialog)
{
    init();
}

LoadingDialog::~LoadingDialog()
{
    delete ui;
}

void LoadingDialog::setVisualWidget(LoadingDialog::VisualWidget which)
{
    m_visualWidget = which;
    switch(which)
    {
    case widgetProgressBar:
        ui->progressBar->show();
        ui->spinner->hide();


        setAttribute(Qt::WA_NoSystemBackground, false);
        setAttribute(Qt::WA_TranslucentBackground, false);
        resize(300,100);

        setWindowFlags( Qt::SubWindow | Qt::Dialog | Qt::WindowTitleHint | Qt::WindowStaysOnTopHint);
        if(parentWidget()!= NULL)
        {

            QPoint parentPos = /*parent->mapToGlobal(*/parentWidget()->pos();
            move(parentPos.x()+parentWidget()->width()/2- width()/2,
                        parentPos.y()+parentWidget()->height()/2- height()/2);
        }

        break;
    case widgetSpinner:
        ui->progressBar->hide();
        ui->spinner->show();

        setWindowFlags( Qt::SubWindow | Qt::Dialog | Qt::WindowTitleHint | Qt::WindowStaysOnTopHint);
        resize(300,150);
        if(parentWidget()!= NULL)
        {
            QPoint parentPos = /*parent->mapToGlobal(*/parentWidget()->pos();
            move(parentPos.x()+parentWidget()->width()/2- width()/2,
                        parentPos.y()+parentWidget()->height()/2- height()/2);
        }
        else
        {
        }

        ui->spinner->setCenterOnlyH(true);
        ui->spinner->setDisableParentWhenSpinning(false);

        break;
    default:
        Q_ASSERT_X(false,"setVisualWidget","no such widget");
        return;
    }
}

void LoadingDialog::setFunc(void (*f)())
{
    m_func = f;
    if(m_worker)
        m_worker->setFunc(f);
}

void LoadingDialog::run()
{
    QThread *t = new QThread();
    if(m_worker==NULL)
    {
        m_worker = new Worker();
        m_worker->setFunc(m_func);
    }
    connect(m_worker,SIGNAL(setProcess(int)),this,SLOT(setProcess(int)));

    m_worker->moveToThread(t);
    connect( t, SIGNAL(started()), m_worker, SLOT(doWork()) );
    connect( m_worker, SIGNAL(workFinished()), t, SLOT(quit()) );

    //automatically delete thread and task object when work is done:
    connect( t, SIGNAL(finished()), m_worker, SLOT(deleteLater()) );
    connect( t, SIGNAL(finished()), t, SLOT(deleteLater()) );
    connect( t, SIGNAL(finished()), this, SLOT(onThreadFinished()) );

    t->start();

    QDialog::show();

    // sync. wait till thread finished
    cycle();
    close();
}

void LoadingDialog::init()
{
    ui->setupUi(this);
    setWindowModality(Qt::ApplicationModal);
    setVisualWidget(widgetSpinner);

    m_func = NULL;
    m_worker = NULL;
    _threadFinished=false;

    initSpinner();
    initProgressBar();
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

void LoadingDialog::initProgressBar()
{
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(100);
    ui->progressBar->setValue(0);
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
    ui->progressBar->setMaximum(0);
    ui->progressBar->setValue(-1);
}

void LoadingDialog::setDefiniteMode()
{
    ui->spinner->setMode(WaitingSpinnerWidget::DefiniteMode);
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(100);
    ui->progressBar->setValue(0);
}

void LoadingDialog::resizeEvent(QResizeEvent *e)
{
    QDialog::resizeEvent(e);
    ui->spinner->updatePosition();
    update();
}

void LoadingDialog::show()
{
    QDialog::show();
    switch(m_visualWidget)
    {
    case widgetProgressBar:
        ui->spinner->hide();
        break;
    case widgetSpinner:
        ui->progressBar->hide();
        break;
    default:
        Q_ASSERT(false);
        return;
    }
}

void LoadingDialog::setProcess(int proc)
{
    ui->spinner->setProcess(proc);
    ui->progressBar->setValue(proc);
    update();
    QApplication::instance()->processEvents();
}

void LoadingDialog::setProcessName(const QString &str)
{
    setWindowTitle(str);
    ui->labelProcessName->setText(str);
}
