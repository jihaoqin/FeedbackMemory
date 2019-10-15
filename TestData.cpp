#include "TestData.h"
#include "Note.h"

TestData::TestData()
{

}

TestData::TestData(ItemVec t, QStringVec a){
    titles = t;
    answers = a;
}

float TestData::correctRate(){
    int rightCount = 0;
    for(int i = 0; i < titles.size(); i++){
        auto str = titles.at(i).second;
        auto ans = answers.at(i);
        if(str == ans){
            rightCount++;
        }
    }
    return rightCount*1.0/titles.size();
}

void TestData::serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer) const{
    writer.StartObject();
    writer.String("answers");
    writer.StartArray();
    for(auto i:answers){
        writer.String(i.toUtf8().data());
    }
    writer.EndArray();
    writer.String("submmited");
    writer.Bool(submmited);
    writer.String("titles");
    writer.StartArray();
    for(auto i:titles){
        i.serialize(writer);
    }
    writer.EndArray();
    writer.EndObject();
}

QVector<Item> TestData::wrongItems(){
    QVector<Item> items;
    for(int i = 0; i < titles.size(); i++){
        auto str = titles.at(i).second;
        auto ans = answers.at(i);
        if(str != ans){
            items.append(titles.at(i));
        }
    }
    return items;
}
