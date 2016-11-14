#ifndef TIMEOUTSENDER_H
#define TIMEOUTSENDER_H

#include <QObject>

class TimeoutSender : public QObject
{
    Q_OBJECT
public:
    explicit TimeoutSender(QObject *parent = 0);
    void startTimer(int msec);

signals:
    void timeout();

public slots:
};

#endif // TIMEOUTSENDER_H
