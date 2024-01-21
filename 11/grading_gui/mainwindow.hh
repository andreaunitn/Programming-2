#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "gradecalculator.hh"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_calculatePushButton_clicked();

private:
    Ui::MainWindow *ui;

    const int MAX_POINTS_N = 800;
    const int MAX_POINTS_G = 120;
    const int MAX_POINTS_P = 250;
    const int MAX_POINTS_E = 5;
};
#endif // MAINWINDOW_HH
