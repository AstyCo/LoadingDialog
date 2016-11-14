#include "timeoutsender.h"
#include <QTimer>
#include <QDebug>

TimeoutSender::TimeoutSender(QObject *parent) : QObject(parent)
{
}

void TimeoutSender::startTimer(int msec)
{
    QTimer *timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SIGNAL(timeout()));
    timer->start(msec);
    qDebug() <<"startTimer";
}
