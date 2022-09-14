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
    QFont newFont("Arial", 12, 0, false);
    ui->plainTextEdit->setFont(newFont);
    activeNoteIndex = 0;
    noteList.append(new Note);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addNewNote()
{
//    if (ui->plainTextEdit->toPlainText().length() > 0){
//        Note* note = new Note();
//        note->addText(ui->plainTextEdit->toPlainText());
//        noteList.append(note);
//        ui->pushButton->setEnabled(0);
////        QListWidgetItem *item = new QListWidgetItem();
////        item->setText(ui->plainTextEdit->toPlainText());
////        ui->listWidget->addItem(item);
//    }
    Note* note = new Note();
    noteList.append(note);
    qDebug() << "noteList.length()" << noteList.length();
    ui->pushButton->setEnabled(0);
    activeNoteIndex = noteList.length() - 1;

    displayNoteData();
}

void MainWindow::displayNoteData()
{
    qDebug() << "Updating listView";
    if (!(noteList.isEmpty())) resetIndex();
    ui->listWidget->clear();
    for (int i = 0; i < noteList.length(); i++){
        QListWidgetItem *item = new QListWidgetItem();
        item->setText(parseStr(noteList.at(i)->getText()));
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

QString MainWindow::parseStr(QString str)
{
    if (str.length()> 20){
        str.truncate(20);
    }
    for (int i = 0; i < str.length(); i++){
        QChar c = str.at(i);
        if (c == '\n'){
         qDebug() << "Found tag at index position" << i;
         str.remove(i, 1);
        }
    }
    return str;
}


void MainWindow::on_plainTextEdit_textChanged()
{
   if (ui->plainTextEdit->toPlainText().length() > 0){
       ui->pushButton->setEnabled(true);
   }
//   if (ui->listWidget->currentRow() > -1){
//    noteList.at(ui->listWidget->currentRow())->addText(ui->plainTextEdit->toPlainText());
//   }

   //на свой страх и риск
   noteList.at(activeNoteIndex)->addText(ui->plainTextEdit->toPlainText()); //потому что по умолчанию нет заметки
   //displayNoteData();

   QString s = ui->plainTextEdit->toPlainText();
   qDebug() << "activeNoteIndex " << activeNoteIndex;
}

void MainWindow::on_pushButton_clicked()
{
    addNewNote();
}



void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    DeleteNotDialog* deleteDialog = new DeleteNotDialog;
    if(deleteDialog->exec() == QDialog::Accepted){
        qDebug() << "current Item Index" << ui->listWidget->currentRow();
        noteList.removeAt(ui->listWidget->currentRow());
        activeNoteIndex = 0;
        ui->listWidget->setCurrentRow(activeNoteIndex);
    }
    displayNoteData();
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    ui->plainTextEdit->clear();
  //  int curI = ui->listWidget->currentRow();
    activeNoteIndex = ui->listWidget->currentRow();
    ui->plainTextEdit->setPlainText(noteList.at(activeNoteIndex)->getText());
}
