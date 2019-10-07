#include "TestResultWidget.h"
#include "Data.h"
#include <QVBoxLayout>
#include "TestDialog.h"
#include <QMessageBox>

TestResultWidget::TestResultWidget(DataPtr p, QWidget *parent) : QWidget(parent)
{
    data = p;
    area = new QScrollArea(this);
    mainLayout = new QVBoxLayout;
    vLayout = new QVBoxLayout;
    vLayout->setAlignment(Qt::AlignTop);
    area->setLayout(vLayout);
    mainLayout->addWidget(area);
    setLayout(mainLayout);
    if(!p){
        return;
    }
    auto tests = p->tests;
    for(auto test:tests){
        addLabel(test);
    }
}


void TestResultWidget::addLabel(TestPtr p){
    QHBoxLayout* lay = new QHBoxLayout;
    QLabel* l = new QLabel(this);
    SelfknownButton* button = new SelfknownButton(this);
    lay->addWidget(l);
    lay->addWidget(button);
    button->setText(QString::fromLocal8Bit("查看"));
    QString str(QString::fromLocal8Bit("测试"));
    if(p->submmited == true){
        str += QString::fromLocal8Bit("已完成,正确率")+QString::number(p->correctRate()*100) + "%";
    }
    else{
        str += QString::fromLocal8Bit("未完成");
    }
    connect(button, &SelfknownButton::beClicked, this, &TestResultWidget::clickedSlot);
    l->setText(str);
    vLayout->addLayout(lay);
    labels.append(l);
    buttons.append(button);
}


void TestResultWidget::clickedSlot(SelfknownButton* p){
    int index = -1;
    for(int i = 0; i < buttons.size(); i++){
        if(buttons.at(i) == p){
            index = i;
        }
    }
    if(index < 0){
        QMessageBox* msg = new QMessageBox;
        return;
    }
    auto items = data->tests.at(index)->titles;
    TestDialog dialog(items);
    dialog.setAnswer(data->tests.at(index)->answers);
    auto code = dialog.exec();
    if(code == QDialog::Accepted){
        auto d = dialog.data();
        if(dialog.submited == true){
            d->submmited = true;
        }
        else{
            d->submmited = false;
        }
        data->tests.replace(index, d);
        updateLabel(index);
    }
    else{
        return;
    }
}


void TestResultWidget::setResource(DataPtr p){
    data = p;
    int size = labels.size();
    for(int i = size-1; i>=0; i--){
        vLayout->removeWidget(labels.at(i));
        vLayout->removeWidget(buttons.at(i));
        labels.at(i)->deleteLater();
        buttons.at(i)->deleteLater();
        labels.pop_back();
        buttons.pop_back();
    }
    auto tests = p->tests;
    for(auto test:tests){
        addLabel(test);
    }
}


void TestResultWidget::updateLabel(int i){
    auto p = data->tests.at(i);
    QString str(QString::fromLocal8Bit("测试"));
    if(p->submmited == true){
        str += QString::fromLocal8Bit("已完成,正确率")+QString::number(p->correctRate()*100) + "%";
    }
    else{
        str += QString::fromLocal8Bit("未完成");
    }
    labels.at(i)->setText(str);
}
