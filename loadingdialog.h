#ifndef LOADINGDIALOG_H
#define LOADINGDIALOG_H

#include "ui_loadingdialog.h"
#include "worker.h"
#include <QDialog>
#include <QThread>
#include <QStack>

#include <QDebug>


namespace Ui {
class LoadingDialog;
}

class LoadingDialog : public QDialog
{
    Q_OBJECT
public:
    explicit LoadingDialog(QWidget *parent = 0);
    virtual ~LoadingDialog();

    void run();

    void setFunc(void (*f)()); ///< Если удобней задать глобальную функцию
    void setWorker(Worker *worker); ///< Если через глобальную функцию не выйдет

    void setUnlimittedMode();
    void setDefiniteMode();

public slots:
    void setProc(int proc); ///< От 0 до 100
    void setProcessName(const QString &str); ///< Имя процесса


private:
    void init();
    void initSpinner();

    void cycle();
private slots:
    void onThreadFinished();

private:
    Ui::LoadingDialog *ui;

    void (*m_func)();
    bool _threadFinished;
    Worker *m_worker;
};

#endif // LOADINGDIALOG_H
