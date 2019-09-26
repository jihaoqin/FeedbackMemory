#ifndef DATA_H
#define DATA_H
#include "UsingName.h"
#include "TestData.h"
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"

class GuiConnector;

class Data
{
public:
    Data();
    void serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer) const;
    NotesPtr notes;
    QVector<TestPtr> tests;
};

#endif // DATA_H
