#ifndef TESTRESULTWIDGET_H
#define TESTRESULTWIDGET_H

#include <QWidget>
#include <QLabel>
#include "TestData.h"
#include "UsingName.h"
#include <QScrollArea>
#include <QVBoxLayout>
#include "SelfknownButton.h"

class TestResultWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TestResultWidget(DataPtr p, QWidget *parent = nullptr);
    void addLabel(TestPtr);
    void setResource(DataPtr);
    void updateLabel(int i);
signals:
    void testIndex(int);

public slots:
    void clickedSlot(SelfknownButton*);
private:
    DataPtr data;
    QVector<QLabel*> labels;
    QVector<SelfknownButton*> buttons;
    QScrollArea* area;
    QVBoxLayout* vLayout;
    QVBoxLayout* mainLayout;
};

#endif // TESTRESULTWIDGET_H
