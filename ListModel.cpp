#include "ListModel.h"
#include "Note.h"

ListModel::ListModel(QObject* parent):QAbstractListModel(parent)
{

}

void ListModel::setResource(NotesPtr p){
    beginResetModel();
    notes = p;
    endResetModel();
}

int ListModel::rowCount(const QModelIndex& parent) const{
    if(parent == QModelIndex() && notes){
        int size = notes->size();
        return size;
    }
    else{
        return 0;
    }
}

int ListModel::columnCount(const QModelIndex& parent) const{
    return 1;
}

QVariant ListModel::data(const QModelIndex& index, int role) const{
    if(index.isValid() && Qt::DisplayRole == role){
        int row = index.row();
        QVariant result = notes->at(row)->meta.name;
        return result;
    }
    else{
        return QVariant();
    }
}

bool ListModel::insertRows(int row, int count, const QModelIndex &parent){
    if(row>=0 && row <= rowCount()){
        beginInsertRows(parent, row, row+count-1);
        notes->insert(row, count, std::make_shared<Note>());
        endInsertRows();
        return true;
    }
    else{
        return false;
    }
}

bool ListModel::removeRows(int row, int count, const QModelIndex& parent){
    if(row>=0 && count <= (rowCount()-row)){
        beginRemoveRows(parent, row, row+count-1);
        notes->remove(row, count);
        endRemoveRows();
        return true;
    }
    else{
        return false;
    }
}

bool ListModel::setData(const QModelIndex& index, const QVariant& value, int role){
    QString str = value.toString();
    if(index.isValid()){
        int row = index.row();
        if(row >= 0 && row <= rowCount()-1){
            NotePtr p = std::make_shared<Note>();
            p->meta.name = str;
            notes->at(row)->meta.name = str;
        }
        emit dataChanged(index, index);
        return true;
    }
    else{
        return false;
    }
}

Qt::ItemFlags ListModel::flags(const QModelIndex &index) const{
    if (!index.isValid())
        return 0;

    return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}
