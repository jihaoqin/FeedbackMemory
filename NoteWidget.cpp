#include "NoteWidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "Note.h"
#include <QFileDialog>
#include <fstream>
#include <sstream>
#include <QMessageBox>
#include "ListDialog.h"

NoteWidget::NoteWidget(QWidget *parent) : QWidget(parent)
{
    workInd = 0;
    addButton = new QPushButton("add", this);
    removeButton = new QPushButton("remove", this);
    importButton = new QPushButton("import", this);
    outportButton = new QPushButton("outport", this);
    QVBoxLayout* buttonLayout = new QVBoxLayout();
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(removeButton);
    buttonLayout->addWidget(importButton);
    buttonLayout->addWidget(outportButton);
    buttonLayout->addStretch();
    view = new QTableView;
    model = new NoteModel;
    view->setModel(model);
    view->setColumnWidth(0, 300);
    view->setColumnWidth(1, 300);
    QHBoxLayout* mainLayout = new QHBoxLayout;

    mainLayout->addWidget(view);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);

    connect(addButton, &QPushButton::clicked, this, &NoteWidget::addItem);
    connect(removeButton, &QPushButton::clicked, this, &NoteWidget::removeItem);
    connect(importButton, &QPushButton::clicked, this, &NoteWidget::importItem);
    connect(outportButton, &QPushButton::clicked, this, &NoteWidget::outputItem);
}

void NoteWidget::setData(NotesPtr p){
    notes = p;
    model->setResource(notes->at(0));
    workInd = 0;
}


void NoteWidget::updatePage(int i){
    if(notes){
        auto & note = notes->at(i);
        model->setResource(note);
        workInd = i;
    }
    else{
        auto temp = std::make_shared<Note>();
        model->setResource(temp);
    }
}


void NoteWidget::addItem(){
    model->insertRows(model->rowCount(), 1);
}

void NoteWidget::removeItem(){
    const QModelIndex& curInd = view->currentIndex();
    int row = curInd.row();
    model->removeRows(row, 1);
}

void NoteWidget::importItem(){
    QString path = QFileDialog::getOpenFileName(this, "import item", "");
    if(path.isEmpty()){
        return ;
    }
    else{
        std::ifstream inFile;
        std::string line;
        inFile.open(path.toLatin1().data());
        QVector<Item> data;
        while(getline(inFile, line)){
            QString str = QString(line.data());
            auto twoStr = str.split(",");
            if(twoStr.size() != 2){
                QMessageBox mesBox(this);
                mesBox.setWindowTitle("warning");
                mesBox.setText("wrong format");
                mesBox.setStandardButtons(QMessageBox::Ok);
                if(mesBox.exec() == QMessageBox::Ok){
                    return;
                }
            }
            data.append(Item{twoStr.first(), twoStr.last()});
        }
        NotePtr p = std::make_shared<Note>();
        p->items = data;
        ListDialog* dialog = new ListDialog;
        dialog->setResource(p);
        if(dialog->exec() != QDialog::Accepted){
            return;
        }
        for(auto& item:data){
            notes->at(workInd)->items.append(item);
        }
        updatePage(workInd);
    }
}

void NoteWidget::outputItem(){
    QString path = QFileDialog::getSaveFileName(this, "output item", "", "*.items");
    if(path.isEmpty()){
        return ;
    }
    std::ofstream outFile;
    QString line;
    outFile.open(path.toLatin1().data());
    int rowCount = model->rowCount();
    for(int i = 0; i<rowCount; i++){
        auto first = model->data(model->index(i, 0)).toString();
        auto second = model->data(model->index(i, 1)).toString();
        line += first + "," + second + "\n";
    }
    std::string str = line.toUtf8().data();
    outFile << str;
    outFile.close();
}

void NoteWidget::addItems(QVector<Item> items){
    assert(0);
}
