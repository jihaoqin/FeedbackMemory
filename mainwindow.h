#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QItemSelection>
#include "UsingName.h"
#include "NoteWidget.h"
#include "TestResultWidget.h"

class QSplitter;
class NoteListWidget;
class MetaWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void setData(DataPtr);
    ~MainWindow();

public slots:
    void updatePages(const QItemSelection &selected, const QItemSelection &deselected);
    void saveFile();
    void openFile();
    void beginTest();
    void lookTest();

private:
    DataPtr dataPtr;
    void createMenus();
    QMenu* fileMenu;
    QMenu* examMenu;
    QSplitter* mainSplitter;
    QSplitter* leftSplitter;
    NoteListWidget* listWidget;
    MetaWidget* metaWidget;
    NoteWidget* tableWidget;
    QAction* openAct;
    QAction* saveAct;
    QAction* beginAct;
    QAction* lookTestAct;
    TestResultWidget* testResultWidget;
};

QVector<int> randomNum(int range, int size);

#endif // MAINWINDOW_H
