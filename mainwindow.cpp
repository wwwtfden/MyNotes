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
    //ui->pushButton->setEnabled(0);
    QFont newFont("Arial", 12, 0, false);
    ui->plainTextEdit->setFont(newFont);
    activeNoteIndex = 0;
  //  noteList.append(new Note);
  //  qDebug() << noteList.at(0);

    QList<Note> lst = dbTools.readFromFile();

    for (int i = 0; i < lst.length(); i++){
        Note* note = new Note;
        note->addText(lst.at(i).getText());
        noteList.append(note);
        qDebug() << note->getText();
    }
    displayNoteData();
    ui->plainTextEdit->setPlainText(noteList.at(activeNoteIndex)->getText());
   // dbTools = new DBWriter();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addNewNote()
{
    Note* note = new Note();
  //  Note note = new Note();
    noteList.append(note);
    qDebug() << "noteList.length()" << noteList.length();
    ui->pushButton->setEnabled(0);
    activeNoteIndex = noteList.length() - 1;
    qDebug() << "activeNoteIndex" << activeNoteIndex;
    ui->listWidget->setCurrentRow(activeNoteIndex);
    ui->plainTextEdit->clear();
    ui->plainTextEdit->setFocus();
    displayNoteData();
}

void MainWindow::displayNoteData()
{
    qDebug() << "Updating listView";
  //  if (!(noteList.isEmpty())) resetIndex();
    ui->listWidget->clear();
    for (int i = 0; i < noteList.length(); i++){
        QListWidgetItem *item = new QListWidgetItem();
        item->setText(parseStr(noteList.at(i)->getText()));
        ui->listWidget->addItem(item);
    }
//    ui->plainTextEdit->clear();
    ui->listWidget->setCurrentRow(activeNoteIndex, QItemSelectionModel::ToggleCurrent);


    dbTools.saveFile(noteList);
    QList<Note> lst = dbTools.readFromFile();

}



QString MainWindow::parseStr(QString str)
{
    if (str.length() == 0) { return "..."; }

    if (str.length()> 25){
        str.truncate(25);
        str = str + "...";
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

   noteList.at(activeNoteIndex)->addText(ui->plainTextEdit->toPlainText()); //потому что по умолчанию нет заметки
   qDebug() << noteList.at(activeNoteIndex)->getText();
   displayNoteData();

   qDebug() << "activeNoteIndex " << activeNoteIndex;
}

void MainWindow::on_pushButton_clicked()
{
    addNewNote();
}



void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{

}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    activeNoteIndex = ui->listWidget->currentRow();

    ui->listWidget->setCurrentRow(activeNoteIndex, QItemSelectionModel::ToggleCurrent); // удалить если что, проба

  //  ui->plainTextEdit->clear();
  //  int curI = ui->listWidget->currentRow();
    ui->plainTextEdit->setPlainText(noteList.at(activeNoteIndex)->getText());
}

void MainWindow::on_pushButton_2_clicked()
{
    DeleteNotDialog* deleteDialog = new DeleteNotDialog;
    if(deleteDialog->exec() == QDialog::Accepted){
        if (noteList.length() >  1){
        qDebug() << "current Item Index" << activeNoteIndex;
        noteList.removeAt(activeNoteIndex);
        if(activeNoteIndex > 0){
        activeNoteIndex--;
        } else {
        activeNoteIndex = 0;
        }
        ui->listWidget->setCurrentRow(activeNoteIndex);
        ui->plainTextEdit->setPlainText(noteList.at(activeNoteIndex)->getText());
        } else {
            noteList.at(0)->addText("");
            ui->plainTextEdit->setPlainText(noteList.at(0)->getText());
            displayNoteData();
        }
    }



    displayNoteData();
}


 //перегрузка операторов

