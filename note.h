#ifndef NOTE_H
#define NOTE_H
#include <QtWidgets>
#include <QDataStream>

class Note
{
public:
    Note();
    ~Note();
    Note(QString insideText);
    void addText(QString text);
    QString getText();
    friend QDataStream& operator>>(QDataStream& d, Note& n);

private:
    QString text;
};



#endif // NOTE_H
