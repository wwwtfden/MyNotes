#include "qexlabel.h"

void QExLabel::mouseReleaseEvent(QMouseEvent *e)
{
        if (e->button() == Qt::RightButton) {
            emit clicked((QObject*)this);
            qDebug() << "img rightbutton clicked";
            pmnu = new QMenu(this);
            QString nameOfDeleteAction = "&Delete Image ";
            pmnu->addAction(nameOfDeleteAction);
            connect(pmnu, SIGNAL(triggered(QAction*)), SLOT(slotMenuActivated(QAction*)));
            pmnu->exec(e->globalPos());
            //emit imgDeleted();
            
        }
}

void QExLabel::mouseDoubleClickEvent(QMouseEvent *e)
{
    emit imgDClicked();
}


void QExLabel::slotMenuActivated(QAction *pAction)
{
    emit imgDeleted();
}
