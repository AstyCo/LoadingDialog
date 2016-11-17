#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "loadingdialog.h"

class I : public QThread
{
public:
    static void sleep(unsigned long secs) {
        QThread::sleep(secs);
    }
    static void msleep(unsigned long msecs) {
        QThread::msleep(msecs);
    }
    static void usleep(unsigned long usecs) {
        QThread::usleep(usecs);
    }
};

namespace Ui {
class MainWindow;
}

class JustTest : public QObject
{
    Q_OBJECT

public:
    virtual ~JustTest(){};
public slots:
    void calcFunc();
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void calcFunc();
private slots:
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();

signals:
    void setProcess(int);

private:

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
