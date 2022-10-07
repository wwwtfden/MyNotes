#include "note.h"

Note::Note()
{
    text = "";
    img = QPixmap(0,0);
  //  qDebug() << "Note::Note() Created img" << img.size();
}

Note::Note(QString text)
{
    this->text = text;
    img = QPixmap(0,0);
  //  QPixmap px(0,0);
 //   img = px;
  //  qDebug() << "Note::Note(QString text) Created img" << img.size();
}

Note::Note(QString text, QPixmap img)
{
    this->text = text;
    this->img = img;
  //  qDebug() << "Note::Note(QString text, QPixmap img) Created img" << this->img.size();
}


void Note::addText(QString text)
{
    this->text = text;
}


QString Note::getText() const
{
    return this->text;
}

QPixmap Note::getImg() const
{
    return this->img;
}

void Note::setImg(const QPixmap &value)
{
    img = value;
    qDebug() << "pixSize " << img.size();
}

void Note::clrImg()
{
   QPixmap tmp;
   img.swap(tmp);
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

