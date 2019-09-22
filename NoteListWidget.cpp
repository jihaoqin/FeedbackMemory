#include "NoteListWidget.h"
#include <QListView>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "ListModel.h"
#include "Note.h"
#include <QStringListModel>
#include <QMenu>
#include "AddDialog.h"

NoteListWidget::NoteListWidget(QWidget* parent):QWidget(parent)
{
    view = new QListView(this);
    model = new ListModel();
    view->setModel(model);
    QHBoxLayout* mainLayout = new QHBoxLayout();
    mainLayout->addWidget(view);
    setLayout(mainLayout);
    connect(view->selectionModel(), &QItemSelectionModel::selectionChanged, this, &NoteListWidget::changed);
}

void NoteListWidget::setData(NotesPtr p){
    model->setResource(p);
    view->setCurrentIndex(model->index(0,0));
}


void NoteListWidget::changed(const QItemSelection &selected, const QItemSelection &deselected){
    emit selectionChanged(selected, deselected);
}

void NoteListWidget::contextMenuEvent(QContextMenuEvent* event){
    QMenu* popMenu = new QMenu(this);
    QAction* addNote = new QAction(QString::fromLocal8Bit("添加"), this);
    QAction* deleteNote = new QAction(QString::fromLocal8Bit("删除"), this);
    popMenu->addAction(addNote);
    popMenu->addAction(deleteNote);
    connect(addNote, &QAction::triggered, this, &NoteListWidget::showAddEntryDialog);

    popMenu->exec(QCursor::pos());
}

void NoteListWidget::showAddEntryDialog(){
    AddDialog dialog;
    if(dialog.exec()){
        QString name = dialog.nameText->text();
        QString word = dialog.wordText->toPlainText();

        addEntry(name);
        emit modifyMetaRequest(model->rowCount()-1, word);
    }
}

void NoteListWidget::addEntry(QString name){
    model->insertRow(model->rowCount());
    model->setData(model->index(model->rowCount()-1), name);

}
