#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

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
    void on_findPushButton_clicked();

private:
    Ui::MainWindow *ui;

    const std::string FILE_NOT_FOUND = "File not found";
    const std::string FILE_FOUND = "File found";
    const std::string WORD_NOT_FOUND = "Word not found";
    const std::string WORD_FOUND = "Word found";
};
#endif // MAINWINDOW_HH
