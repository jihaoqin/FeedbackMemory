#include "NoteWidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "Note.h"

NoteWidget::NoteWidget(QWidget *parent) : QWidget(parent)
{
    workInd = 0;
    addButton = new QPushButton("add", this);
    removeButton = new QPushButton("remove", this);
    importButton = new QPushButton("import", this);
    QVBoxLayout* buttonLayout = new QVBoxLayout();
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(removeButton);
    buttonLayout->addWidget(importButton);
    buttonLayout->addStretch();
    view = new QTableView;
    model = new NoteModel;
    view->setModel(model);
    view->setColumnWidth(0, 300);
    view->setColumnWidth(1, 300);
    QHBoxLayout* mainLayout = new QHBoxLayout;

    mainLayout->addWidget(view);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);

    connect(addButton, &QPushButton::clicked, this, &NoteWidget::addItem);
}

void NoteWidget::setData(NotesPtr p){
    notes = p;
    model->setResource(notes->at(0));
    workInd = 0;
}


void NoteWidget::updatePage(int i){
    if(notes){
        auto & note = notes->at(i);
        model->setResource(note);
        workInd = i;
    }
    else{
        auto temp = std::make_shared<Note>();
        model->setResource(temp);
    }
}


void NoteWidget::addItem(){
    model->insertRows(model->rowCount(), 1);
}
