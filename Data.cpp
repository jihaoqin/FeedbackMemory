#include "Data.h"

Data::Data()
{

}

void Data::serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer) const{
    writer.StartArray();
    const QVector<NotePtr>& data = *notes;
    for(auto &i:data){
        i->serialize(writer);
    }
    writer.EndArray();
}
