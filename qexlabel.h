#ifndef QEXLABEL_H
#define QEXLABEL_H
#include <QLabel>
#include <QWidget>
#include <QMouseEvent>
#include <QDebug>
#include <QMenu>
class QExLabel : public QLabel {
    Q_OBJECT
public:
    explicit QExLabel(QWidget* parent = 0)
        : QLabel(parent){};
signals:
    void clicked(QObject* sender);
    void imgDeleted();
protected:
    void mouseReleaseEvent(QMouseEvent* e);
private:
    QMenu* pmnu;
public slots:
    void slotMenuActivated(QAction* pAction);
};
#endif // QEXLABEL_H
