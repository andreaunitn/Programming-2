#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

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

std::string toLower(const std::string& str) {
    std::string lowerStr;
    for (char ch : str) {
        lowerStr += std::tolower(static_cast<unsigned char>(ch));
    }
    return lowerStr;
}

void MainWindow::on_findPushButton_clicked()
{
    QString file_name = ui->fileLineEdit->text();
    QString search_word = ui->keyLineEdit->text();
    std::string search_word_str = search_word.toStdString();

    QString result = "";

    std::ifstream file(file_name.toStdString());
    if(!file)
    {
        result = QString::fromStdString(FILE_NOT_FOUND);
        ui->textBrowser->setText(result);
        return;
    }

    qDebug() << search_word;

    if(search_word == "")
    {
        result = QString::fromStdString(FILE_FOUND);
        ui->textBrowser->setText(result);
        return;
    }

    std::string word;
    while(file >> word)
    {
        if(ui->matchCheckBox->isChecked())
        {
            if(search_word_str == word)
            {
                result = QString::fromStdString(WORD_FOUND);
                ui->textBrowser->setText(result);
                return;
            }
        } else
        {
            if(toLower(word) == toLower(search_word_str))
            {
                result = QString::fromStdString(WORD_FOUND);
                ui->textBrowser->setText(result);
                return;
            }
        }
    }

    result = QString::fromStdString(WORD_NOT_FOUND);
    ui->textBrowser->setText(result);

    file.close();
}

