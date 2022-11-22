#include "dbwriter.h"

DBWriter::DBWriter(QObject* parent): QObject(parent)
{

    qDebug() << "DBWriter initialize";
    dbFile = new QFile();
    dbFile->setFileName(QApplication::applicationDirPath() + "/database.bin");
    if (dbFile->exists()){
        qDebug() << "File opened";
    }
    else {
        qDebug() << "File created";
    }
}

DBWriter::~DBWriter()
{
    qDebug() << "DBWriter снесло";
    delete dbFile;
}




//void DBWriter::saveFile(QList<Note*> list)
void DBWriter::saveFile(QList<QSharedPointer<Note>> list)
{
    qDebug() << "Function of saving file";
    dbFile->open(QIODevice::WriteOnly | QIODevice::Truncate); //сначала откроем файл для перезаписи
    QDataStream fileOutStream(dbFile); //откроем поток вывода в файл
    for (int i = 0; i < list.length(); i++){
       // Note tNote(list.at(i)->getText());
        Note tNote(list.at(i)->getText(), list.at(i)->getImg());
       // qDebug() << "Img to save at note " << i << " size " << tNote.getImg().size();
        QString tmpTxt = tNote.getText();
        QPixmap tmpImg = tNote.getImg();
        int index = i;
        fileOutStream << index << tmpTxt << tmpImg;

      //  fileOutStream << tNote;
       // qDebug() << "Convertation text " << i << " " << list.at(i)->getText() << " size " << tNote.getImg().size();
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
        QString tmpTxt;
        QPixmap tmpImg;
        int index;
        //fileInStream >> tNote2;
        fileInStream >> index >> tmpTxt >> tmpImg;
        tNote2.setImg(tmpImg);
        tNote2.addText(tmpTxt);

        temp.append(tNote2);
        qDebug() << "tNote2.getText()" << tNote2.getText() <<tNote2.getImg().size(); // добавил дебаг картинки
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



