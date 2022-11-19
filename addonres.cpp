#include "addonres.h"
#include "ui_addonres.h"

AddOnRes::AddOnRes(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddOnRes)
{
    setBaseSize(480,272);
    setWindowTitle("Viewer");

    QPalette pal;
    pal.setColor(QPalette::Background, Qt::black);
    setAutoFillBackground(true);
    setPalette(pal);

    ui->setupUi(this);
}

AddOnRes::~AddOnRes()
{
    delete ui;
}

QPixmap AddOnRes::getPix() const
{
    return pix;
}

void AddOnRes::setPix(const QPixmap &value)
{
    pix = value;
    pixF = pix.scaled(QSize(ui->label->width(), ui->label->height()), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label->setPixmap(pixF);
    ui->label->repaint();
}

void AddOnRes::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    ui->label->clear();
    pixF = pix.scaled(QSize(ui->label->width(), ui->label->height()), Qt::KeepAspectRatio, Qt::SmoothTransformation);
   ui->label->setPixmap(pixF);
   ui->label->repaint();
}
