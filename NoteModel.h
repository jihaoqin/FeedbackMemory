#ifndef NOTEMODEL_H
#define NOTEMODEL_H
#include <QAbstractTableModel>
#include "UsingName.h"
#include "Note.h"

class NoteModel:public QAbstractTableModel
{
    Q_OBJECT
public:
    void setResource(NotePtr);
    NoteModel(QObject* parent=nullptr);
    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    virtual int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool insertRows(int row, int count, const QModelIndex& parent = QModelIndex()) override;
    void setItem(int, Item);
private:
    NotePtr note;
};

#endif // NOTEMODEL_H
