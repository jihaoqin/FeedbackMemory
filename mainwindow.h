#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QItemSelection>
#include "UsingName.h"
#include "NoteWidget.h"

class QSplitter;
class NoteListWidget;
class MetaWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void setData(NotesPtr);
    ~MainWindow();

public slots:
    void updatePages(const QItemSelection &selected, const QItemSelection &deselected);

private:
    void createMenus();
    QMenu* fileMenu;
    QSplitter* mainSplitter;
    QSplitter* leftSplitter;
    NoteListWidget* listWidget;
    MetaWidget* metaWidget;
    NoteWidget* tableWidget;
    QAction* openAct;
    QAction* saveAct;
};

#endif // MAINWINDOW_H
