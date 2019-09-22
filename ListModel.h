#ifndef LISTMODEL_H
#define LISTMODEL_H
#include "UsingName.h"
#include <QAbstractListModel>

class ListModel:public QAbstractListModel
{
    Q_OBJECT
public:
    ListModel(QObject* parent = NULL);
    void setResource(NotesPtr);
    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    virtual int	columnCount(const QModelIndex & parent = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    virtual bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
    virtual bool removeRows(int row, int count, const QModelIndex& parent = QModelIndex());
    virtual bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole);
    virtual Qt::ItemFlags flags(const QModelIndex &index) const override;
private:
    NotesPtr notes;
};

#endif // LISTMODEL_H
