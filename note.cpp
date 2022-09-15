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

QString Note::getText()
{
    return this->text;
}

//int Note::getIndex()
//{
//    return this->index;
//}


QDataStream& operator<<(QDataStream& d, Note &item) {
    d << item.getText();
    return d;
}

QDataStream& operator>>(QDataStream& d, Note &item) {
    d >> item.text;
    return d;
}

QDebug operator<<(QDebug d, Note &item) {
    d << QString("Note( %1 )").arg(item.getText());
    return d;
}
