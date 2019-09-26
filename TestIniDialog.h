#ifndef TESTINIDIALOG_H
#define TESTINIDIALOG_H

#include <QDialog>
#include <QCheckBox>
#include <QSlider>
#include "UsingName.h"
#include <QLabel>

class TestIniDialog:public QDialog
{
    Q_OBJECT
public:
    TestIniDialog(NotesPtr, QWidget* parent = nullptr);
    void updatePage();
    QVector<int> choiceIndex();
    int totalNum();
public slots:
    void updateNum();
private:
    void setResource(NotesPtr);
    QSlider* quantitySlider;
    QLabel* numberLabel;
    QPushButton* okButton;
    QPushButton* cancleButton;
    QVector<QCheckBox*> boxs;
    NotesPtr data;
    int total;
};

#endif // TESTINIDIALOG_H
