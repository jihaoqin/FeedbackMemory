#include "mainwindow.h"
#include <QApplication>
#include <QVector>
#include "UsingName.h"
#include "Note.h"
#include "Data.h"
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    NotesPtr notes = std::make_shared<QVector<NotePtr>>();
    NotePtr english = std::make_shared<Note>();
    english->meta.name = QString::fromLocal8Bit("错题本");
    english->meta.detail = "";
    english->items.push_back(Item{"1", "ahead"});
    notes->push_back(english);


    NotePtr chs = std::make_shared<Note>();
    chs->meta.name = QString::fromLocal8Bit("日本語");
    chs->meta.detail = QString::fromLocal8Bit("");
    chs->items.push_back(Item{"fadf", "ahead"});
    notes->push_back(chs);

    DataPtr data = std::make_shared<Data>();
    data->notes = notes;

    MainWindow w;
    w.setData(data);
    w.show();

    return a.exec();
}
