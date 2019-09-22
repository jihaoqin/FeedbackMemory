#include "mainwindow.h"
#include <QSplitter>
#include <QSplitterHandle>
#include <QLabel>
#include "NoteListWidget.h"
#include "MetaWidget.h"
#include <QMenuBar>
#include <QMenu>
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    resize(1000,600);
    createMenus();
    mainSplitter = new QSplitter(Qt::Horizontal, this);
    leftSplitter = new QSplitter(Qt::Vertical, mainSplitter);
    listWidget = new NoteListWidget(this);
    listWidget->setMinimumWidth(100);
    metaWidget = new MetaWidget(this);
    metaWidget->setMinimumHeight(200);
    tableWidget = new NoteWidget(this);

    leftSplitter->addWidget(listWidget);
    leftSplitter->addWidget(metaWidget);
    leftSplitter->setStretchFactor(0, 3);
    leftSplitter->setStretchFactor(1, 1);

    mainSplitter->addWidget(leftSplitter);
    mainSplitter->addWidget(tableWidget);
    mainSplitter->setHandleWidth(2);
    mainSplitter->setStyleSheet("QSplitter::handle { background-color: black }");
    mainSplitter->setStretchFactor(0,1);
    mainSplitter->setStretchFactor(1,10);
    setCentralWidget(mainSplitter);
    connect(listWidget, &NoteListWidget::selectionChanged, this, &MainWindow::updatePages);
    connect(listWidget, &NoteListWidget::modifyMetaRequest, metaWidget, &MetaWidget::modifyMeta);
}

MainWindow::~MainWindow()
{
}


void MainWindow::setData(NotesPtr p){
    listWidget->setData(p);
    metaWidget->setData(p);
    tableWidget->setData(p);
}


void MainWindow::updatePages(const QItemSelection &selected, const QItemSelection &deselected){
    QModelIndexList indexes = selected.indexes();

    if (!indexes.isEmpty()) {
        auto i = indexes.at(0);
        metaWidget->updatePage(i.row());
        tableWidget->updatePage(i.row());
    } else {
    }
}

void MainWindow::createMenus(){
    fileMenu = menuBar()->addMenu(tr("&File"));

    openAct = new QAction(tr("&Open..."), this);
    fileMenu->addAction(openAct);
    //connect(openAct, &QAction::triggered, this, &MainWindow::openFile);

    saveAct = new QAction(tr("&Save As..."), this);
    fileMenu->addAction(saveAct);
    //connect(saveAct, &QAction::triggered, this, &MainWindow::saveFile);

    fileMenu->addSeparator();

}
