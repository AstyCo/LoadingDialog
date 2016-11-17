#ifndef WORKER_H
#define WORKER_H

#include <QObject>

class Worker : public QObject
{
    Q_OBJECT

public:
    explicit Worker(QObject *parent = 0);

    void setFunc(void (*f)()){
        m_func = f;
    }

public slots:
    virtual void doWork();

signals:
    void workFinished();
    void setProcess(int newValue);

private:
    void (*m_func)();
};

#endif // WORKER_H
