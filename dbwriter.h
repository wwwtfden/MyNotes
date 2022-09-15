#ifndef DBWRITER_H
#define DBWRITER_H
#include <QtWidgets>
#include <QFile>
#include <QObject>
#include "note.h"
#include <QList>
//static const char* const FILE_NAME = "db.bin";

class DBWriter  : public QObject
{

public:
    explicit DBWriter(QObject *parent = 0);
    void write(QList<Note*> nl);
    void read();
    void saveFile(QList<Note*> list);

private:
    QFile* dbFile;
 //   Note toNote;
 //   QDataStream oStream (QFile &file);
  //  QDataStream oStream;
};




#endif // DBWRITER_H
