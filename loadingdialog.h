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
    enum VisualWidget
    {
        widgetSpinner,
        widgetProgressBar
    };

    explicit LoadingDialog(Worker *worker,QWidget *parent = 0);
    explicit LoadingDialog(QWidget *parent = 0);
    virtual ~LoadingDialog();

    void setVisualWidget(LoadingDialog::VisualWidget which);

    void setFunc(void (*f)()); ///< Если удобней задать глобальную функцию
    void setWorker(Worker *worker); ///< Если через глобальную функцию не выйдет

    void setUnlimittedMode();
    void setDefiniteMode();

protected:
    void resizeEvent(QResizeEvent *);

public slots:
    void show();
    void run();

    void setProcess(int proc); ///< От 0 до 100
    void setProcessName(const QString &str); ///< Имя процесса

private:
    void init();
    void initSpinner();
    void initProgressBar();

    void cycle();
private slots:
    void onThreadFinished();

private:
    Ui::LoadingDialog *ui;

    void (*m_func)();
    bool _threadFinished;
    Worker *m_worker;
    VisualWidget m_visualWidget;
};

#endif // LOADINGDIALOG_H
