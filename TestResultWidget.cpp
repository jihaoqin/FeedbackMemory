#include "TestResultWidget.h"
#include "Data.h"
#include <QVBoxLayout>

TestResultWidget::TestResultWidget(DataPtr p, QWidget *parent) : QWidget(parent)
{
    area = new QScrollArea(this);
    QVBoxLayout* vLayout = new QVBoxLayout;
    if(!p){
        return;
    }
    auto tests = p->tests;
    for(auto test:tests){
        QLabel* l = new QLabel(this);
        QString str(QString::fromLocal8Bit("测试"));
        if(test->submmited == true){
            str += QString::fromLocal8Bit("已完成") ;
        }
        else{
            str += QString::fromLocal8Bit("未完成");
        }
        l->setText(str);
        vLayout->addWidget(l);
    }
    area->setLayout(vLayout);
    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(area);
    setLayout(mainLayout);
}
