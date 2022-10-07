#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <note.h>
#include <QtWidgets>
#include <QList>
#include <dbwriter.h>
//#include "addonres.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void displayNoteData();
    QString parseStr(QString str);
    void resizeEvent(QResizeEvent* event);
    void createMenuData();

public slots:
    void addNewNote();
    void setImageToNote();
    void drawImage();

    bool eventFilter(QObject *watched, QEvent *event);
    void deleteImg();

    void saveDbFile();

    void closeEvent(QCloseEvent* e) override;

private slots:
    void on_plainTextEdit_textChanged();

    void on_pushButton_clicked();


   // void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_pushButton_2_clicked();


    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    QList<Note*> noteList;
    int activeNoteIndex;
    bool savedFlag;

    DBWriter dbTools;
   // AddOnRes aResWidget;

    QPixmap tmpImg;
    QPixmap tmpImg2;


};
#endif // MAINWINDOW_H
