#ifndef NOTE_H
#define NOTE_H
#include <QtWidgets>

class Note
{
public:
    Note();
    Note(QString insideText);
    void addText(QString text);

private:
    QString text;
};

#endif // NOTE_H
