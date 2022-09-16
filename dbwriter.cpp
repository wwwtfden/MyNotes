#include "dbwriter.h"

DBWriter::DBWriter(QObject* parent): QObject(parent)
{

    qDebug() << "DBWriter initialize";
    dbFile = new QFile();
    dbFile->setFileName(QApplication::applicationDirPath() + "/database.bin");
    if (dbFile->exists()){
        qDebug() << "File created";
    }
}




void DBWriter::saveFile(QList<Note*> list)
{
    dbFile->open(QIODevice::WriteOnly | QIODevice::Truncate); //сначала откроем файл для перезаписи
    QDataStream fileOutStream(dbFile); //откроем поток вывода в файл
    for (int i = 0; i < list.length(); i++){
        Note tNote(list.at(i)->getText());
        fileOutStream << tNote;
        qDebug() << "Convertation text " << i << " " << list.at(i)->getText();
    }
    dbFile->flush();
    dbFile->close();
}



QList<Note> DBWriter::readFromFile()
{
    QList <Note> temp;
    dbFile->open(QIODevice::ReadOnly);
    QByteArray buf = dbFile->readAll();
    QDataStream fileInStream(&buf, QIODevice::ReadOnly);
    while(!fileInStream.atEnd()){
        Note tNote2;
        fileInStream >> tNote2;
        temp.append(tNote2);
        qDebug() << "tNote2.getText()" << tNote2.getText();
    }

    for (int i = 0; i < temp.length(); i++){
           qDebug() << "Builded QList test:" << i << " " << temp.at(i).getText();
    }
    dbFile->close();
    if (temp.length() == 0) {
        Note emptyNote("");
        temp.append(emptyNote);
    }
    return temp;
}



