#include "Note.h"

Note::Note()
{

}


int Note::size(){
    return items.size();
}


Item Note::at(int index){
    return items.at(index);
}

void Note::serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer) const{
    writer.StartObject();
    writer.String("type");
    writer.String("Note");
    writer.EndObject();
}

void NoteMeta::serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer) const{
    writer.StartObject();
    writer.String("type");
    writer.String("NoteMeta");
    writer.String("name");
    writer.String(meta.name.toLatin1().data());
    writer.String("detail");
    writer.String(meta.detail.toLatin1().data());
    for(auto& item:items){
        item->serialize(writer);
    }
    writer.EndObject();
}

void Item::serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer) const{
    writer.StartObject();
    writer.String("type");
    writer.String("Item");
    writer.String("first");
    writer.String(first.toLatin1().data());
    writer.String("second");
    writer.String(second.toLatin1().data());
    writer.EndObject();
}