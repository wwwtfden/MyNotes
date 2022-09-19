#ifndef ADDONRES_H
#define ADDONRES_H

#include <QWidget>

namespace Ui {
class AddOnRes;
}

class AddOnRes : public QWidget
{
    Q_OBJECT

public:
    explicit AddOnRes(QWidget *parent = nullptr);
    ~AddOnRes();

private:
    Ui::AddOnRes *ui;
};

#endif // ADDONRES_H
