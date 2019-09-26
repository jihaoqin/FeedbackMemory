#ifndef TESTWIDGET_H
#define TESTWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include "Note.h"

class TestWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TestWidget(QVector<Item> resource, QWidget *parent = nullptr);
    QVector<QString> data();
private:
    QVector<Item> items;
    QVector<QLabel*> labels;
    QVector<QLineEdit*> edits;
};

#endif // TESTWIDGET_H
