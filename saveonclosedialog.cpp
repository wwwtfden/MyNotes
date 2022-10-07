#include "saveonclosedialog.h"

SaveOnCloseDialog::SaveOnCloseDialog(QWidget* parent) : QDialog(parent, Qt::WindowTitleHint | Qt::WindowSystemMenuHint)
{
    setWindowTitle("Warning!");
        QBoxLayout* baseLayout = new QVBoxLayout;
        QBoxLayout* layout = new QHBoxLayout;
        QPushButton* okButton = new QPushButton("&Ok");
        connect( okButton, &QAbstractButton::clicked, this, &QDialog::accept );
        QPushButton* cancelButton = new QPushButton("&Cancel");
        connect( cancelButton, &QAbstractButton::clicked, this, &QDialog::reject );
        QLabel* lbl = new QLabel("Save database file?");
        layout->addWidget(okButton);
        layout->addWidget(cancelButton);
        baseLayout->addWidget(lbl);
        baseLayout->addLayout(layout);
        setLayout(baseLayout);
}




