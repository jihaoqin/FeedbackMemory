#ifndef TESTRESULTWIDGET_H
#define TESTRESULTWIDGET_H

#include <QWidget>
#include <QLabel>
#include "TestData.h"
#include "UsingName.h"
#include <QScrollArea>

class TestResultWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TestResultWidget(DataPtr p, QWidget *parent = nullptr);

signals:

public slots:
private:
    QVector<QLabel*> labels;
    QScrollArea* area;
};

#endif // TESTRESULTWIDGET_H
