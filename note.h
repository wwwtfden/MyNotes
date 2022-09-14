#ifndef NOTE_H
#define NOTE_H
#include <QtWidgets>

class Note
{
public:
    Note();
    ~Note();
    Note(QString insideText);
    void addText(QString text);
  //  void setIndex(int num);
    QString getText();
  //  int getIndex();

private:
  //  int index;
    QString text;
};

#endif // NOTE_H
