#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <note.h>
#include <QtWidgets>
#include <QList>
#include <dbwriter.h>


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

public slots:
    void addNewNote();

private slots:
    void on_plainTextEdit_textChanged();

    void on_pushButton_clicked();


    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_pushButton_2_clicked();


private:
    Ui::MainWindow *ui;
    QList<Note*> noteList;
    int activeNoteIndex;

    DBWriter dbTools;

};
#endif // MAINWINDOW_H
