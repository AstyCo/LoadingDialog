#include "specialworker.h"
#include "mainwindow.h"

SpecialWorker::SpecialWorker():
    Worker()
{
    _mw=0;
}

void SpecialWorker::setMainWindow(MainWindow *mw)
{
    _mw=mw;
    connect(_mw,SIGNAL(setProcess(int)),this,SIGNAL(setProcess(int)));
}

void SpecialWorker::doWork()
{
    if(_mw)
        _mw->calcFunc();

    emit workFinished(); // Worker::doWork(); ///< Можно так, если не вызывалась setFunc()
}
