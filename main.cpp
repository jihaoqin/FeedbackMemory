#include "mainwindow.h"
#include <QApplication>
#include <QVector>
#include "UsingName.h"
#include "Note.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    NotesPtr notes = std::make_shared<QVector<NotePtr>>();
    NotePtr english = std::make_shared<Note>();
    english->meta.name = "English";
    english->meta.detail = "boring\n interesting";
    english->items.push_back(Item{"1", "ahead"});
    notes->push_back(english);


    NotePtr chs = std::make_shared<Note>();
    chs->meta.name = "Chinese";
    chs->meta.detail = QString::fromLocal8Bit("你好");
    chs->items.push_back(Item{"fadf", "ahead"});
    notes->push_back(chs);

    MainWindow w;
    w.setData(notes);
    w.show();

    return a.exec();
}
