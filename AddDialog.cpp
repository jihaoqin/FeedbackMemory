#include "AddDialog.h"
#include <QLineEdit>
#include <QTextEdit>
#include <QGridLayout>
#include <QPushButton>
#include <QHBoxLayout>


AddDialog::AddDialog(QWidget* parent):QDialog(parent)
{
    nameLabel = new QLabel("title:", this);
    wordLabel = new QLabel("description:", this);
    nameText = new QLineEdit(this);
    wordText = new QTextEdit(this);
    QGridLayout* gridLay = new QGridLayout;
    gridLay->addWidget(nameLabel, 0, 0);
    gridLay->addWidget(nameText, 0, 1);
    gridLay->addWidget(wordLabel, 1, 0);
    gridLay->addWidget(wordText, 1, 1);
    okButton = new QPushButton("ok");
    cancelButton = new QPushButton("cancle");
    QHBoxLayout* buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);
    gridLay->addLayout(buttonLayout, 2, 0);
    setLayout(gridLay);

    connect(okButton, &QAbstractButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QAbstractButton::clicked, this, &QDialog::reject);
}
