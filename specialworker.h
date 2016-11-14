#ifndef SPECIALWORKER_H
#define SPECIALWORKER_H

#include "worker.h"

class MainWindow;

class SpecialWorker : public Worker
{
    Q_OBJECT
public:
    SpecialWorker();
    void setMainWindow(MainWindow *mw);

public slots:
    void doWork();

private:
    MainWindow *_mw;
};

#endif // SPECIALWORKER_H
