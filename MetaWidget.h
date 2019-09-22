#ifndef METAWIDGET_H
#define METAWIDGET_H
#include <QLabel>
#include "UsingName.h"

class MetaWidget:public	QLabel
{
    Q_OBJECT
public:
    MetaWidget(QWidget*);
    void setData(NotesPtr);
    void updatePage(int);
public slots:
    void modifyMeta(int, QString);
private:
    NotesPtr notes;
};

#endif // METAWIDGET_H
