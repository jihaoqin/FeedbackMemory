#ifndef NOTELISTWIDGET_H
#define NOTELISTWIDGET_H
#include <QListWidget>
#include "UsingName.h"

class ListModel;

class NoteListWidget:public QWidget
{
    Q_OBJECT
public:
    NoteListWidget(QWidget*);
    void setData(NotesPtr);
    void addEntry(QString name);
signals:
    void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
    void modifyMetaRequest(int, QString);
protected:
    void contextMenuEvent(QContextMenuEvent* event) override;
public slots:
    void changed(const QItemSelection &selected, const QItemSelection &deselected);
    void showAddEntryDialog();

private:
    QListView* view;
    ListModel* model;
};

#endif // NOTELISTWIDGET_H
