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
#include <QFileDialog>
#include "Note.h"
#include <fstream>
#include "TestIniDialog.h"
#include "TestDialog.h"
#include "TestData.h"
#include "Data.h"

using namespace rapidjson;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    resize(1000,600);
    createMenus();
    testResultWidget = new TestResultWidget(dataPtr, this);
    mainSplitter = new QSplitter(Qt::Horizontal);
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
    mainSplitter->addWidget(testResultWidget);
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


void MainWindow::setData(DataPtr p){
    dataPtr = p;
    listWidget->setData(p->notes);
    metaWidget->setData(p->notes);
    tableWidget->setData(p->notes);
    testResultWidget->setResource(p);
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
    examMenu = menuBar()->addMenu(tr("&Exam"));

    openAct = new QAction(tr("&Open..."), this);
    fileMenu->addAction(openAct);
    connect(openAct, &QAction::triggered, this, &MainWindow::openFile);

    saveAct = new QAction(tr("&Save As..."), this);
    fileMenu->addAction(saveAct);
    connect(saveAct, &QAction::triggered, this, &MainWindow::saveFile);

    beginAct = new QAction(tr("&Begin test"), this);
    examMenu->addAction(beginAct);
    connect(beginAct, &QAction::triggered, this, &MainWindow::beginTest);

    lookTestAct = new QAction("&Result", this);
    examMenu->addAction(lookTestAct);
    connect(lookTestAct, &QAction::triggered, this, &MainWindow::lookTest);
    fileMenu->addSeparator();

}

void MainWindow::saveFile(){
    QString fileName = QFileDialog::getSaveFileName(this, "save note", "", "*.notes");
    if(fileName.isEmpty()){
        return ;
    }
    else{
        if(dataPtr){
            StringBuffer sb;
            PrettyWriter<StringBuffer> writer(sb);
            dataPtr->serialize(writer);
            std::ofstream outFile;
            outFile.open(fileName.toLatin1().data());
            outFile<<sb.GetString();
            outFile.close();
        }
        else{
            return;
        }
    }
}

void MainWindow::beginTest(){
    TestIniDialog* dialog = new TestIniDialog(dataPtr->notes);
    if(dialog->exec() == QDialog::Rejected){
        return;
    }
    auto indexs = dialog->choiceIndex();
    if(indexs.size() == 0){
        return;
    }
    QVector<Item> items;
    for(auto i:indexs){
        auto& testSet = dataPtr->notes->at(i)->items;
        for(auto item:testSet){
            items.append(item);
        }
    }
    QVector<int> problemIndexs = randomNum(items.size(), dialog->totalNum());
    QVector<Item> resource;
    for(auto i:problemIndexs){
        resource.push_back(items.at(i));
    }
    TestDialog* testDialog = new TestDialog(resource, this);
    auto code = testDialog->exec();
    if(code == QDialog::Accepted){
        auto testD = testDialog->data();
        if(testDialog->submited == true){
            testD->submmited = true;
            dataPtr->tests.append(testD);
        }
        else{
            testD->submmited = false;
            dataPtr->tests.append(testD);
        }
        testResultWidget->addLabel(testD);
    }
    else{
        return;
    }
}

QVector<int> randomNum(int range, int size){
    QSet<int> choice;
    QVector<int> result;
    srand(time(0));
    for(int i = 0; i < size; i++){
        int num;
        do{
            num = rand()%range;
        }while(choice.find(num) != choice.end());
        result.push_back(num);
        choice.insert(num);
    }
    return result;
}

void MainWindow::lookTest(){
    TestResultWidget* widget = new TestResultWidget(dataPtr);
    widget->show();
}


void MainWindow::openFile(){
    QString fileName = QFileDialog::getOpenFileName(this, "open note", "", "*.notes");
    if(fileName.isEmpty()){
        return;
    }
    std::ifstream inFile;
    std::string line;
    std::string allLine;
    inFile.open(fileName.toLatin1().data());
    while(getline(inFile, line)){
        allLine.append(line+"\n");
    }
    Document doc;
    doc.Parse<0>(allLine.c_str());
    if(doc.HasParseError()){
        return ;
    }
    std::shared_ptr<Data> data = dataPtr;
    const Value& obj = doc;
    const Value& notes = obj["notes"];
    DataPtr dataP = std::make_shared<Data>();
    dataP->notes = std::make_shared<QVector<NotePtr>>();
    for(auto j = 0; j<notes.Size(); j++){
        NotePtr note = std::make_shared<Note>();
        const Value& notej = notes[j];
        const Value& meta = notej["meta"];
        QString name = meta["name"].GetString();
        QString detail = meta["detail"].GetString();
        note->meta.name = name;
        note->meta.detail = detail;
        const Value& itemArray = notej["itemArray"];
        for(int i = 0; i<itemArray.Size(); i++){
            const Value& item = itemArray[i];
            QString first = item["first"].GetString();
            QString second = item["second"].GetString();
            note->items.append({first, second});
        }
        dataP->notes->append(note);
    }
    const Value& tests = obj["tests"];
    for(auto i = 0; i<tests.Size(); i++){
        TestPtr testP = std::make_shared<TestData>();
        const Value& test = tests[i];
        const Value& answers = test["answers"];
        for(auto j = 0; j<answers.Size(); j++){
            testP->answers.append(answers[j].GetString());
        }
        testP->submmited = test["submmited"].GetBool();
        const Value& titles = test["titles"];
        for(auto j = 0; j<titles.Size(); j++){
            const Value& t = titles[j];
            testP->titles.append(Item{t["first"].GetString(), t["second"].GetString()});
        }
        dataP->tests.append(testP);
    }
    setData(dataP);
}
