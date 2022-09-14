#include "note.h"

Note::Note()
{
    text = "";
    index = 999;
}

Note::Note(QString insideText)
{
    text = insideText;
}


void Note::addText(QString text)
{
    this->text = text;
}

void Note::setIndex(int index)
{
    this->index = index;
}

QString Note::getText()
{
    return this->text;
}

int Note::getIndex()
{
    return this->index;
}
