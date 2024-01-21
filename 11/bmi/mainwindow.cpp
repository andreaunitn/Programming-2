#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_countButton_clicked()
{
    QString weight = ui->weightLineEdit->text();
    QString height = ui->heightLineEdit->text();

    QString result = "";

    if(height == "0" || height == "")
    {
        result = "Cannot count";
        ui->resultLabel->setText(result);
        return;
    }

    bool ok;
    float w = weight.toFloat(&ok);
    float h = height.toFloat(&ok);
    h = h / 100;

    if(!ok)
    {
        return;
    }

    float bmi = w / (h * h);

    if(bmi < 18.5)
    {
        result = "Underweight";
    } else if (bmi > 25)
    {
        result = "Overweight";
    } else
    {
        result = "Normal range";
    }

    QString bmi_str = QString::number(bmi);

    ui->resultLabel->setText(bmi_str);
    ui->infoTextBrowser->setText(result);
}

