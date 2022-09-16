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
    QFont newFont("Arial", 12, 0, false);
    ui->plainTextEdit->setFont(newFont);
    activeNoteIndex = 0;

    QList<Note> lst = dbTools.readFromFile(); //читаем файл базы данных

    for (int i = 0; i < lst.length(); i++){ // инициализируем коллекцию заметок из буфера, который мы создали из файла
        Note* note = new Note(lst.at(i).getText());
        noteList.append(note);
        qDebug() << note->getText();
    }
    displayNoteData();
    ui->plainTextEdit->setPlainText(noteList.at(activeNoteIndex)->getText()); //инициализируем текстовое поле первой заметкой
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addNewNote()
{
    Note* note = new Note();
    noteList.append(note); //заметки добавляются в конец QList
    qDebug() << "noteList.length()" << noteList.length();
    ui->pushButton->setEnabled(0);
    activeNoteIndex = noteList.length() - 1; //меняем флаг активной заметки на индекс новой заметки
    qDebug() << "activeNoteIndex" << activeNoteIndex;
    ui->listWidget->setCurrentRow(activeNoteIndex); //делаем активной позицию данной заметки в виджете списка
    ui->plainTextEdit->clear();
    ui->plainTextEdit->setFocus();
    displayNoteData();
}

void MainWindow::displayNoteData() //тут обновляем элементы интерфейса
{
    qDebug() << "Updating listView";
    ui->listWidget->clear();
    for (int i = 0; i < noteList.length(); i++){
        QListWidgetItem *item = new QListWidgetItem();
        item->setText(parseStr(noteList.at(i)->getText()));
        ui->listWidget->addItem(item);
    }
    ui->listWidget->setCurrentRow(activeNoteIndex, QItemSelectionModel::ToggleCurrent);


    dbTools.saveFile(noteList); //здесь при каждом изменении обновляется база данных
    //QList<Note> lst = dbTools.readFromFile();

}

QString MainWindow::parseStr(QString str)  //парсинг элемента виджета списка, для стандартизации внешнего вида
{
    if (str.length() == 0) { return "..."; }
    if (str.length()> 25){
        str.truncate(25);
        str = str + "...";
    }
    for (int i = 0; i < str.length(); i++){
        QChar c = str.at(i);
        if (c == '\n'){
       //  qDebug() << "Found tag at index position" << i;
      //   str.remove(i, 1);
         str.replace(i,1,' ');
        }
    }
    return str;
}


void MainWindow::on_plainTextEdit_textChanged() // при изменении текста в plainTextEdit приходим сюда
{
   if (ui->plainTextEdit->toPlainText().length() > 0){ //включаем кнопку добавления
       ui->pushButton->setEnabled(true);
   }

   noteList.at(activeNoteIndex)->addText(ui->plainTextEdit->toPlainText()); //потому что по умолчанию нет заметки
   qDebug() << noteList.at(activeNoteIndex)->getText();
   displayNoteData();

   qDebug() << "activeNoteIndex " << activeNoteIndex; //для контроля того, что флаг активной заметки установлен правильно
}

void MainWindow::on_pushButton_clicked()
{
    addNewNote();
}



//void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
//{

//}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    activeNoteIndex = ui->listWidget->currentRow();
    ui->listWidget->setCurrentRow(activeNoteIndex, QItemSelectionModel::ToggleCurrent); // удалить если что, проба
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

