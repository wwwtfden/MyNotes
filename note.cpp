#include "note.h"

Note::Note()
{
    text = "";
}

Note::Note(QString text)
{
    this->text = text;
}


void Note::addText(QString text)
{
    this->text = text;
}


QString Note::getText() const
{
    return this->text;
}


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

