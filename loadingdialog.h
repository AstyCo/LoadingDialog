#ifndef LOADINGDIALOG_H
#define LOADINGDIALOG_H

#include <QDialog>
#include <QThread>


namespace Ui {
class LoadingDialog;
}

class LoadingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoadingDialog(QWidget *parent = 0);
    ~LoadingDialog();



private:
    void init();
    void initSpinner();

private:
    Ui::LoadingDialog *ui;

    QThread *_currentThread,
            *_newThread;
};

#endif // LOADINGDIALOG_H
