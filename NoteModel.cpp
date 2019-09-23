#include "NoteModel.h"
#include "Note.h"

NoteModel::NoteModel(QObject* parent):QAbstractTableModel(parent)
{

}

int NoteModel::rowCount(const QModelIndex& parent) const{
    if(note){
        return note->size();
    }
    else{
        return 0;
    }
}

int NoteModel::columnCount(const QModelIndex& parent ) const{
    return 2;
}
QVariant NoteModel::data(const QModelIndex& index, int role) const{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= note->size() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole && note) {
        const auto &item = note->at(index.row());

        if (index.column() == 0)
            return item.first;
        else if (index.column() == 1)
            return item.second;
    }
    return QVariant();
}


void NoteModel::setResource(NotePtr p){
    beginResetModel();
    note = p;
    endResetModel();
}

bool NoteModel::setData(const QModelIndex &index, const QVariant &value,
                        int role){
    if (role != Qt::EditRole)
        return false;

    int col = index.column();
    int row = index.row();
    QString str = value.toString();
    QString firstStr = note->items.at(row).first;
    QString secondStr = note->items.at(row).second;
    if(str.isEmpty()){
        return false;
    }
    if(col == 0){
        note->items.replace(row, Item{str, secondStr});
    }
    else{
        note->items.replace(row, Item{firstStr, str});
    }

    emit dataChanged(index, index);

    return true;
}

Qt::ItemFlags NoteModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}


bool NoteModel::insertRows(int row, int count, const QModelIndex& parent){
    if(row >=0 && row<=rowCount() && count>0){
        beginInsertRows(parent, row, row+count-1);
        note->items.insert(row, count, Item());
        endInsertRows();
        return true;
    }
    else{
        return false;
    }
}

void NoteModel::setItem(int row, Item value){
    note->items.replace(row, value);
}

bool NoteModel::removeRows(int row, int count, const QModelIndex& parent){
    if(row >=0 && row <= rowCount() && count>0){
        beginRemoveRows(parent, row, row+count-1);
        note->items.remove(row, count);
        endRemoveRows();
        return true;
    }
    else{
        return false;
    }
}
