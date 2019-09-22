#ifndef NOTEWIDGET_H
#define NOTEWIDGET_H

#include <QWidget>
#include "QTableView"
#include "NoteModel.h"

class NoteWidget : public QWidget
{
    Q_OBJECT
public:
    explicit NoteWidget(QWidget *parent = nullptr);
    void setData(NotesPtr);
    void updatePage(int);

signals:

public slots:
private:
    QTableView* view;
    NoteModel* model;
    NotesPtr notes;
};

#endif // NOTEWIDGET_H
