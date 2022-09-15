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
//    if(dbFile->exists() && dbFile->isOpen()){
//            dbFile->flush();
//            dbFile->close();
//            dbFile->flush();
//        }
}


void DBWriter::flush()
{
    if(dbFile->exists() && dbFile->isOpen()){
        dbFile->flush();
    }
}


bool DBWriter::isReady()
{
    if(dbFile->exists() && dbFile->isOpen()){
        return true;
    } else {
        return false;
    }
}

void DBWriter::read()
{
    if(dbFile->isOpen()){
         qDebug() << "File opened for reading";
         QDataStream iStream(dbFile);
         Note tempNote;
         iStream >> tempNote;
         qDebug() << "Text from file:" << tempNote.getText();
    }
}



void DBWriter::write(QList<Note*> nl)
{
    qDebug() << "DBWriter::write";
  //  dbFile->open(QIODevice::Truncate);
    if(dbFile->isOpen())
    {
        qDebug() << "File opened for writing";
        QDataStream oStream(dbFile);
        Note* tempNote = nl.at(0);
       // QDataStream s2(dbFile);
        qDebug() << "For write: " << tempNote << nl.at(0)->getText();
        oStream << tempNote;


    }
}

