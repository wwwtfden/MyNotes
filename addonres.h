#ifndef ADDONRES_H
#define ADDONRES_H

#include <QWidget>
#include <QLayout>
#include <QLabel>

namespace Ui {
class AddOnRes;
}

class AddOnRes : public QWidget
{
    Q_OBJECT

public:
  //  AddOnRes(AddOnRes &other) = delete;
    AddOnRes(QWidget *parent = nullptr);
    ~AddOnRes();

    QPixmap getPix() const;
    void setPix(const QPixmap &value);
    void resizeEvent(QResizeEvent* event);
    static bool instance;

private:
    Ui::AddOnRes *ui;
    QPixmap pix;
    QPixmap pixF;
    //   QLayout layout;
};

#endif // ADDONRES_H
