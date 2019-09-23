#include "ListDialog.h"
#include <QHBoxLayout>
#include <QVBoxLayout>

ListDialog::ListDialog(QWidget* parent):QDialog (parent)
{
    view = new QTableView(this);
    okButton = new QPushButton("ok", this);
    cancleButton = new QPushButton("no", this);
    model = new NoteModel();
    view->setModel(model);
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancleButton);
    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addWidget(view);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);
    connect(okButton, &QPushButton::pressed, this, &ListDialog::accept);
    connect(cancleButton, &QPushButton::pressed, this, &ListDialog::reject);
}


void ListDialog::setResource(NotePtr p){
    model->setResource(p);
}

