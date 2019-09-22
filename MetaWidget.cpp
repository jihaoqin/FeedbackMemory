#include "MetaWidget.h"
#include "Note.h"

MetaWidget::MetaWidget(QWidget* parent):QLabel(parent)
{
    setAlignment(Qt::AlignTop | Qt::AlignLeft);
}

void MetaWidget::setData(NotesPtr p){
    notes = p;
    updatePage(0);
}

void MetaWidget::updatePage(int index){
    if(notes){
        QString detail = notes->at(index)->meta.detail;
        setText(detail);
    }
    else{
        setText("");
    }
}

void MetaWidget::modifyMeta(int row, QString str){
    notes->at(row)->meta.detail = str;
}
