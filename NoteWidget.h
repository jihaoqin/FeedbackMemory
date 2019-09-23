#ifndef NOTEWIDGET_H
#define NOTEWIDGET_H

#include <QWidget>
#include "QTableView"
#include "NoteModel.h"
#include <QPushButton>

class NoteWidget : public QWidget
{
    Q_OBJECT
public:
    explicit NoteWidget(QWidget *parent = nullptr);
    void setData(NotesPtr);
    void updatePage(int);

signals:

public slots:
    void addItem();
    void removeItem();
    void importItem();
private:
    QTableView* view;
    NoteModel* model;
    NotesPtr notes;
    int workInd;
    QPushButton* addButton;
    QPushButton* removeButton;
    QPushButton* importButton;
};

#endif // NOTEWIDGET_H
