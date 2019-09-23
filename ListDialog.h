#ifndef LISTDIALOG_H
#define LISTDIALOG_H
#include <QDialog>
#include <QPushButton>
#include <QTableView>
#include "NoteModel.h"
#include "UsingName.h"

class ListDialog:public QDialog
{
    Q_OBJECT
public:
    ListDialog(QWidget* parent = nullptr);
    void setResource(NotePtr);
private:
    QTableView* view;
    NoteModel* model;
    QPushButton* okButton;
    QPushButton* cancleButton;
};

#endif // LISTDIALOG_H
