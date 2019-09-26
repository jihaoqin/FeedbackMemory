#ifndef NOTE_H
#define NOTE_H
#include <QString>
#include <QMap>
#include <QVector>
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"

class NoteMeta{
public:
    QString name;
    QString newTime;
    QString modifyTime;
    QString detail;
    void serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer) const;
};

class Item{
public:
    QString first;
    QString second;
    void serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer) const;
};

using ItemVec = QVector<Item>;


class Note
{
public:
    Note();
    NoteMeta meta;
    int size();
    Item at(int);
    QVector<Item> items;
    void serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer) const;
};

#endif // NOTE_H
