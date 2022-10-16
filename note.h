#ifndef NOTE_H
#define NOTE_H
#include <QtWidgets>
#include <QDataStream>
//#include <QHash>

class Note
{
public:
    Note();
    Note(QString text);
    Note(QString text, QPixmap img);
    ~Note();
    void addText(QString text);
    QString getText() const;
    friend QDataStream& operator>>(QDataStream& d, Note &n);
    friend QDataStream& operator<<(QDataStream& d,const Note &n);


    QPixmap getImg() const;
    void setImg(const QPixmap &value);
    void clrImg();

private:
    QString text;
    QPixmap img;
//    unsigned int key;
};

//QDataStream& operator<<(QDataStream& d, Note *&n);
//QDataStream& operator>>(QDataStream& d, Note &n);
//QDebug operator<<(QDebug d, const Note &n);


#endif // NOTE_H
