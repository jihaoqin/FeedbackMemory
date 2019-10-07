#ifndef TESTDATA_H
#define TESTDATA_H

#include "Note.h"
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"

using QStringVec = QVector<QString>;

class TestData
{
public:
    TestData();
    TestData(ItemVec t, QStringVec a);
    float correctRate();
    void serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer) const;
    bool submmited;
    QVector<QString> answers;
    QVector<Item> titles;
private:
};

#endif // TESTDATA_H
