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
    writer.String("meta.name");
    writer.String(meta.name.toLatin1().data());
    writer.EndObject();
}
