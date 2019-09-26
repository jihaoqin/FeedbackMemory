#ifndef TESTDATA_H
#define TESTDATA_H

#include "Note.h"
using QStringVec = QVector<QString>;

class TestData
{
public:
    TestData();
    TestData(ItemVec t, QStringVec a);
    bool submmited;
private:
    QVector<Item> titles;
    QVector<QString> answers;
};

#endif // TESTDATA_H
