#include "NoteWidget.h"
#include <QHBoxLayout>
#include "Note.h"

NoteWidget::NoteWidget(QWidget *parent) : QWidget(parent)
{
    view = new QTableView;
    model = new NoteModel;
    view->setModel(model);
    view->setColumnWidth(0, 300);
    view->setColumnWidth(1, 300);
    QHBoxLayout* mainLayout = new QHBoxLayout;
    mainLayout->addWidget(view);
    setLayout(mainLayout);
}

void NoteWidget::setData(NotesPtr p){
    notes = p;
    model->setResource(notes->at(0));
}


void NoteWidget::updatePage(int i){
    if(notes){
        auto & note = notes->at(i);
        model->setResource(note);
    }
    else{
        auto temp = std::make_shared<Note>();
        model->setResource(temp);
    }
}
