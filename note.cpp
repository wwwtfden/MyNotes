#include "note.h"

Note::Note()
{
    text = "";
 //   index = 999;
}

//Note::Note(QString insideText)
//{
//    text = insideText;
//}


void Note::addText(QString text)
{
    this->text = text;
}

//void Note::setIndex(int index)
//{
//    this->index = index;
//}

QString Note::getText() const
{
    return this->text;
}

//int Note::getIndex()
//{
//    return this->index;
//}




//QDebug operator<<(QDebug d, const Note &n) {
//    d << QString("Note( %1 )").arg(n.getText());
//    return d;
//}

QDataStream &operator<<(QDataStream &d,const Note &n)
{
    d << n.getText();
       return d;
}

QDataStream &operator>>(QDataStream &d, Note &n)
{
    d >> n.text;
    return d;
}

