#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), seconds_(0), minutes_(0)
{
    ui->setupUi(this);

    ui->lcdNumberMin->setStyleSheet("background-color:red;");
    ui->lcdNumberSec->setStyleSheet("background-color:green;");

    timer = new QTimer();

    connect(timer, &QTimer::timeout, this, &MainWindow::updateTimer);
}

MainWindow::~MainWindow()
{
    delete timer;
    delete ui;
}

void MainWindow::on_startButton_clicked()
{
    if(!timer->isActive())
    {
        timer->start(1000);
    }
}


void MainWindow::on_stopButton_clicked()
{
    timer->stop();
}


void MainWindow::on_resetButton_clicked()
{
    ui->lcdNumberMin->display(0);
    ui->lcdNumberSec->display(0);

    seconds_ = 0;
    minutes_ = 0;
}

void MainWindow::updateTimer()
{
    seconds_++;

    if(seconds_ >= 60)
    {
        minutes_++;
        seconds_ = 0;
    }

    ui->lcdNumberMin->display(minutes_);
    ui->lcdNumberSec->display(seconds_);
}
