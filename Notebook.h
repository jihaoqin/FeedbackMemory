#ifndef NOTEBOOK_H
#define NOTEBOOK_H
#include "UsingName.h"
#include <QVector>
#include <memory>

class Notebook
{
public:
    Notebook();
private:
    NotesPtr notes;
};

#endif // NOTEBOOK_H
