#include "loadingdialog.h"
#include "ui_loadingdialog.h"

LoadingDialog::LoadingDialog(QWidget *parent) :
    QDialog(parent,Qt::Window | Qt::FramelessWindowHint),
    ui(new Ui::LoadingDialog)
{
    ui->setupUi(this);
    init();
    setAttribute(Qt::WA_NoSystemBackground, true);
    setAttribute(Qt::WA_TranslucentBackground, true);

}

LoadingDialog::~LoadingDialog()
{
    delete ui;
}

void LoadingDialog::init()
{
    _currentThread = QThread::currentThread();
    _newThread = NULL;
    initSpinner();
}

void LoadingDialog::initSpinner()
{
    ui->spinner->setRoundness(70.0);
    ui->spinner->setMinimumTrailOpacity(15.0);
    ui->spinner->setTrailFadePercentage(70.0);
    ui->spinner->setNumberOfLines(12);
    ui->spinner->setLineLength(10);
    ui->spinner->setLineWidth(5);
    ui->spinner->setInnerRadius(10);
    ui->spinner->setRevolutionsPerSecond(1);

    ui->spinner->start(); // gets the show on the road!
}
