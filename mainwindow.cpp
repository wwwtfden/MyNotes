#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>

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

void MainWindow::addNewNote()
{
    Note note;
    note.addText(ui->plainTextEdit->toPlainText());
    noteList.append(note);

    qDebug() << noteList.length();
}


void MainWindow::on_plainTextEdit_textChanged()
{
   QString s = ui->plainTextEdit->toPlainText();
   qDebug() << s;
}

void MainWindow::on_pushButton_clicked()
{
    addNewNote();
}
