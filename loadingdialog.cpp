#include "loadingdialog.h"
#include "ui_loadingdialog.h"

#include <QDebug>
#include <QTime>
#include <QKeyEvent>
#include <QThread>
#include "timeoutsender.h"

LoadingDialog::LoadingDialog(QWidget *parent) :
    QDialog(parent,Qt::Window /*| Qt::FramelessWindowHint*/),
    ui(new Ui::LoadingDialog)
{
    ui->setupUi(this);
    init();
//    setAttribute(Qt::WA_NoSystemBackground, true);
//    setAttribute(Qt::WA_TranslucentBackground, true);

}

LoadingDialog::~LoadingDialog()
{
    delete ui;
}

void LoadingDialog::keyPressEvent(QKeyEvent *event)
{
    qDebug() <<"keyPressEvent "<<event;
    if(event->key()==Qt::Key_Escape)
        close();
    QWidget::keyPressEvent(event);
}

void LoadingDialog::init()
{
    _currentThread = QThread::currentThread();
    _newThread = NULL;
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


void LoadingDialog::onTimeout()
{
    qDebug() << "onTimeout";
    qDebug() << QTime::currentTime();

    QApplication::processEvents();
}
