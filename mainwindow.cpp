#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>
#include <deletenotdialog.h>
#include <saveonclosedialog.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createMenuData();
    savedFlag = false;

    this->setWindowTitle("Note Editor");
    QFont newFont("Arial", 12, 0, false);
    ui->plainTextEdit->setFont(newFont);
    activeNoteIndex = 0;

    QList<Note> lst = dbTools.readFromFile(); //читаем файл базы данных

    for (int i = 0; i < lst.length(); i++){ // инициализируем коллекцию заметок из буфера, который мы создали из файла
      //  Note* note = new Note(lst.at(i).getText());
        Note* note = new Note(lst.at(i).getText(), lst.at(i).getImg());
        noteList.append(note);
        qDebug() << note->getText();
    }
    displayNoteData();
    ui->plainTextEdit->setPlainText(noteList.at(activeNoteIndex)->getText()); //инициализируем текстовое поле первой заметкой
    connect(ui->label, &QExLabel::imgDeleted, this, &MainWindow::deleteImg);

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

    drawImage();
    savedFlag = false;
 //   dbTools.saveFile(noteList); //здесь при каждом изменении обновляется база данных
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

void MainWindow::setImageToNote()
{
    QString fName = QFileDialog::getOpenFileName();
    qDebug() << fName;
    if(tmpImg.load(fName)){
        noteList[activeNoteIndex]->setImg(tmpImg);
        qDebug() << "image loaded";
        displayNoteData();
    }
    else qDebug() << "err";
}

void MainWindow::drawImage()
{
    ui->label->clear();
    tmpImg2 = noteList[activeNoteIndex]->getImg().scaled(QSize(ui->label->width(), ui->label->height()), Qt::KeepAspectRatio, Qt::SmoothTransformation);
  //  qDebug() << tmpImg2.size();
  // ui->label->update();
   ui->label->setPixmap(tmpImg2);
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


void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    activeNoteIndex = ui->listWidget->currentRow();
    ui->listWidget->setCurrentRow(activeNoteIndex, QItemSelectionModel::ToggleCurrent); // удалить если что, проба
    ui->plainTextEdit->setPlainText(noteList.at(activeNoteIndex)->getText());

    //test function
    displayNoteData();
   // drawImage();
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
        //drawImage();
        displayNoteData();

        } else {
            noteList.at(0)->addText("");
            ui->plainTextEdit->setPlainText(noteList.at(0)->getText());
            displayNoteData();
        }
    }
    displayNoteData();
}


void MainWindow::on_pushButton_3_clicked()
{
    setImageToNote();
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
   QMainWindow::resizeEvent(event);
   qDebug() << ui->label->size();
//   tmpImg2 = tmpImg.scaled(QSize(ui->label->width(), ui->label->height()), Qt::KeepAspectRatio, Qt::SmoothTransformation);
//   ui->label->setPixmap(tmpImg2);
 //   drawImage();
   displayNoteData();
}

void MainWindow::createMenuData()
{
    //Создаем менюху с пунктом save
    QMenu *fileMenu = new QMenu("File");
    QAction *saveAction = new QAction("Save", fileMenu);
    connect(saveAction, &QAction::triggered, this, &MainWindow::saveDbFile);
    fileMenu->addAction(saveAction);

    QAction *closeAction = new QAction("Close", fileMenu);
    connect(closeAction, &QAction::triggered, this, &MainWindow::forceCloseApp);
    fileMenu->addAction(closeAction);

    ui->menubar->addMenu(fileMenu);

}

void MainWindow::forceCloseApp()
{
    if (!savedFlag){
       SaveOnCloseDialog* saveOnCloseDialog = new SaveOnCloseDialog;
       if (saveOnCloseDialog->exec() == QDialog::Accepted){
           saveDbFile();
            qDebug() << "Save on close completed!";
            QApplication::quit();
       } else if (saveOnCloseDialog->exec() == QDialog::Rejected) {
           QApplication::quit();
       }
    } else {
        QApplication::quit();
    }
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->label)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            //обрабатываешь щелчёк мышки по лейблу
            qDebug() << event->type();
        }
    }


    return false;
}

void MainWindow::deleteImg()
{
    //index = activeNoteIndex;
    noteList.at(activeNoteIndex)->clrImg();
    //drawImage();
    displayNoteData();
}

void MainWindow::saveDbFile()
{
    qDebug() << "SLOT(saveDbFile()";
    savedFlag = true;
    dbTools.saveFile(noteList);
}

void MainWindow::closeEvent(QCloseEvent *e)
{
    qDebug() << "Close event terminated.";
    forceCloseApp();
}
