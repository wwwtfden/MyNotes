#include "addonres.h"
#include "ui_addonres.h"

AddOnRes::AddOnRes(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddOnRes)
{
    ui->setupUi(this);
}

AddOnRes::~AddOnRes()
{
    delete ui;
}
