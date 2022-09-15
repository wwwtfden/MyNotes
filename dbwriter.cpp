#include "dbwriter.h"

DBWriter::DBWriter(QObject* parent): QObject(parent)
{

    qDebug() << "DBWriter initialize";
    dbFile = new QFile();
    dbFile->setFileName(QApplication::applicationDirPath() + "database.bin");
    dbFile->open(QIODevice::ReadWrite);
    if (dbFile->exists()){
        qDebug() << "File created";
        dbFile->flush();
    }
}



void DBWriter::read()
{
    if(dbFile->isOpen()){
         qDebug() << "File opened for reading";
         QDataStream iStream(dbFile);
         Note tempNote;
   //      iStream >> tempNote;
         qDebug() << "Text from file:" << tempNote.getText();
    }
}

void DBWriter::saveFile(QList<Note*> list)
{
    QByteArray bar;
    QDataStream barOutStream(&bar, QIODevice::WriteOnly);
    //for (int i = 0; i < list.length(); i++){
        Note tNote;
        tNote.addText( list.at(0)->getText());
        barOutStream << tNote;
        qDebug() << "Convertation text " << list.at(0)->getText();
  //  }
    QDataStream barInStream(&bar, QIODevice::ReadOnly);
    Note tNote2;
    barInStream >> tNote2;
    qDebug() << "tNote2.getText()" << tNote2.getText();
}



void DBWriter::write(QList<Note*> nl)
{
    qDebug() << "DBWriter::write";
//  //  dbFile->open(QIODevice::Truncate);
//    if(dbFile->isOpen())
//    {
//        qDebug() << "File opened for writing";
//        QDataStream oStream(dbFile);
//        Note* tempNote = nl.at(0);
//       // QDataStream s2(dbFile);
//        qDebug() << "For write: " << tempNote << nl.at(0)->getText();
//        oStream << tempNote;
//    }


}

