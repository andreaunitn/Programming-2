#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->spinBoxN->setMinimum(0);
    ui->spinBoxN->setMaximum(MAX_POINTS_N);

    ui->spinBoxG->setMinimum(0);
    ui->spinBoxG->setMaximum(MAX_POINTS_G);

    ui->spinBoxP->setMinimum(0);
    ui->spinBoxP->setMaximum(MAX_POINTS_P);

    ui->spinBoxE->setMinimum(0);
    ui->spinBoxE->setMaximum(MAX_POINTS_E);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_calculatePushButton_clicked()
{
    QString n_points = ui->spinBoxN->text();
    QString g_points = ui->spinBoxG->text();
    QString p_points = ui->spinBoxP->text();
    QString exam_grade = ui->spinBoxE->text();

    QString result = "";

    bool ok;
    unsigned int n = n_points.toUInt(&ok);
    unsigned int g = g_points.toUInt(&ok);
    unsigned int p = p_points.toUInt(&ok);
    unsigned int e = exam_grade.toUInt(&ok);

    if(!ok)
    {
        return;
    }

    unsigned int w_total = score_from_weekly_exercises(n,g);
    unsigned int p_total = score_from_projects(p);

    unsigned int e_total = calculate_total_grade(n, g, p, e);

    QString w_total_str = QString::number(w_total);
    QString p_total_str = QString::number(p_total);
    QString e_total_str = QString::number(e_total);

    result += "W-Score: " + w_total_str + "\nP-Score: " + p_total_str + "\nTotal grade: " + e_total_str;
    ui->textBrowser->setText(result);
}

