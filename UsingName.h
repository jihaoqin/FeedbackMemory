﻿#ifndef USINGNAME_H
#define USINGNAME_H
#include <memory>
#include <QVector>

class Note;
class Notebook;
using NotePtr = std::shared_ptr<Note>;
using NotesPtr = std::shared_ptr<QVector<NotePtr>>;
using NotebookPtr = std::shared_ptr<Notebook>;


#endif // USINGNAME_H