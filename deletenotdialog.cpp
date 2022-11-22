#include "deletenotdialog.h"

DeleteNotDialog::DeleteNotDialog(QWidget* parent) : QDialog(parent, Qt::WindowTitleHint | Qt::WindowSystemMenuHint)
{
    setWindowTitle("Warning!");
    QBoxLayout* baseLayout = new QVBoxLayout;
    QBoxLayout* layout = new QHBoxLayout;
    QPushButton* okButton = new QPushButton("&Ok");
    connect(okButton, &QAbstractButton::clicked, this, &QDialog::accept);
    QPushButton* cancelButton = new QPushButton("&Cancel");
    connect(cancelButton, &QAbstractButton::clicked, this, &QDialog::close);
    QLabel* lbl = new QLabel("Are you sure want to delete this note?");
    //layout->addWidget(lbl);
    layout->addWidget(okButton);
    layout->addWidget(cancelButton);
    baseLayout->addWidget(lbl);
    baseLayout->addLayout(layout);
    setLayout(baseLayout);
    setAttribute(Qt::WA_DeleteOnClose); //удаляем при закрытии
}
