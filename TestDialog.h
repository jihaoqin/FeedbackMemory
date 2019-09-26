#ifndef TESTDIALOG_H
#define TESTDIALOG_H
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QScrollArea>
#include "Note.h"
#include "TestWidget.h"
#include "TestData.h"
#include "UsingName.h"

class TestDialog: public QDialog
{
    Q_OBJECT
public:
    TestDialog(QVector<Item> resource, QWidget* parent = nullptr);
    TestPtr data();
    bool submited;
public slots:
    void submit();
    void store();
private:
    QVector<Item> items;
    TestWidget* testWidget;
    QScrollArea* area;
    QPushButton* overButton;
    QPushButton* storeButton;
};

#endif // TESTDIALOG_H
