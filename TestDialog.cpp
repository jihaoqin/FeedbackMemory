#include "TestDialog.h"
#include <QScrollArea>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QKeyEvent>

TestDialog::TestDialog(QVector<Item> resource, QWidget* parent):QDialog(parent)
{
    items = resource;
    submited = false;
    testWidget = new TestWidget(items, this);
    area = new QScrollArea(this);
    area->setWidget(testWidget);
    QHBoxLayout* lay = new QHBoxLayout;
    QVBoxLayout* vLay = new QVBoxLayout;
    overButton = new QPushButton(QString::fromLocal8Bit("提交"), this);
    storeButton = new QPushButton(QString::fromLocal8Bit("暂存"), this);
    vLay->addWidget(overButton);
    vLay->addWidget(storeButton);
    lay->addWidget(area);
    lay->addLayout(vLay);
    setLayout(lay);
    connect(overButton, &QPushButton::clicked, this, &TestDialog::submit);
    connect(storeButton, &QPushButton::clicked, this, &TestDialog::store);
    resize(1500, 800);
}

TestPtr TestDialog::data(){
    auto as = testWidget->data();
    TestPtr d = std::make_shared<TestData>(items, as);
    return d;
}

void TestDialog::submit(){
    submited = true;
    emit accepted();
    accept();
}

void TestDialog::store(){
    submited = false;
    emit accepted();
    accept();
}

void TestDialog::setAnswer(QStringVec answers){
    testWidget->setAnswers(answers);
}

void TestDialog::keyPressEvent(QKeyEvent* event) {
    auto key = event->key();
    if(key == Qt::Key_Escape){

    }
    else{
        QDialog::keyPressEvent(event);
    }
}
