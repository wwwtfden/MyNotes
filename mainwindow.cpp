#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>
#include <deletenotdialog.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Note Editor");
    ui->pushButton->setEnabled(0);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addNewNote()
{
    if (ui->plainTextEdit->toPlainText().length() > 0){
        Note* note = new Note();
        note->addText(ui->plainTextEdit->toPlainText());
        noteList.append(note);
        ui->pushButton->setEnabled(0);
//        QListWidgetItem *item = new QListWidgetItem();
//        item->setText(ui->plainTextEdit->toPlainText());
//        ui->listWidget->addItem(item);
    }
    displayNoteData();
    qDebug() << noteList.length();
}

void MainWindow::displayNoteData()
{
    qDebug() << "Updating listView";
    if (!(noteList.isEmpty())) resetIndex();
    ui->listWidget->clear();
    for (int i = 0; i < noteList.length(); i++){
        QListWidgetItem *item = new QListWidgetItem();
        item->setText(noteList.at(i)->getText());
        ui->listWidget->addItem(item);
    }
    ui->plainTextEdit->clear();
}

void MainWindow::resetIndex()
{
    for (int i = 0; i<noteList.length(); i++){
        noteList.at(i)->setIndex(i);
    }
}


void MainWindow::on_plainTextEdit_textChanged()
{
   if (ui->plainTextEdit->toPlainText().length() > 0){
       ui->pushButton->setEnabled(true);
   }
   QString s = ui->plainTextEdit->toPlainText();
 //  qDebug() << s;
}

void MainWindow::on_pushButton_clicked()
{
    addNewNote();
}



void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    DeleteNotDialog* deleteDialog = new DeleteNotDialog;
    // takeIndex->setIndexValidator(waypointsRoute.count());
    if(deleteDialog->exec() == QDialog::Accepted){
        qDebug() << "current Item Index" << ui->listWidget->currentRow();
        noteList.removeAt(ui->listWidget->currentRow());
    }
    displayNoteData();
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    ui->plainTextEdit->clear();
    ui->plainTextEdit->setPlainText(item->text());
}
