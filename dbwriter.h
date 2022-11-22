#ifndef DBWRITER_H
#define DBWRITER_H
#include <QtWidgets>
#include <QFile>
#include <QObject>
#include "note.h"
#include <QList>

class DBWriter  : public QObject
{

public:
    explicit DBWriter(QObject *parent = 0);
    ~DBWriter();
    QList<Note> readFromFile();
    void saveFile(QList<QSharedPointer<Note>> list);
;

private:
    QFile* dbFile;
  //  QByteArray bar;

};

#endif // DBWRITER_H
