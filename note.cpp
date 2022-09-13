#include "note.h"

Note::Note()
{
    text = "";
}

Note::Note(QString insideText)
{
    text = insideText;
}


void Note::addText(QString text)
{
    this->text = text;
}
