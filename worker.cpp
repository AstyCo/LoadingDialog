#include "worker.h"


Worker::Worker(QObject *parent):
    QObject(parent)
{

}

void Worker::doWork()
{
    if(m_func != NULL)
    {
        (*m_func)();
    }

    emit workFinished();
}

