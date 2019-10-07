#include "Data.h"

Data::Data()
{

}

void Data::serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer) const{
    writer.StartObject();
    writer.String("notes");
    writer.StartArray();
    const QVector<NotePtr>& data = *notes;
    for(auto &i:data){
        i->serialize(writer);
    }
    writer.EndArray();
    writer.String("tests");
    writer.StartArray();
    for(auto &i:tests){
        i->serialize(writer);
    }
    writer.EndArray();
    writer.EndObject();
}
