#include "TestWidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>

TestWidget::TestWidget(QVector<Item> resource, QWidget *parent) : QWidget(parent)
{
    items = resource;
    QVBoxLayout* mainLayout = new QVBoxLayout;
    for(auto item:items){
        QLabel* title = new QLabel(item.first, this);
        QFont font;
        font.setPointSize(24);
        title->setFont(font);
        QLineEdit* key = new QLineEdit(this);
        labels.append(title);
        edits.append(key);
        QHBoxLayout* lay = new QHBoxLayout;
        lay->addWidget(title);
        lay->addWidget(key);
        mainLayout->addLayout(lay);
    }
    setLayout(mainLayout);
}


QVector<QString> TestWidget::data(){
    QVector<QString> as;
    for(auto p:edits){
        QString a = p->text();
        as.push_back(a);
    }
    return as;
}

void TestWidget::setAnswers(QStringVec answers){
    for(int i = 0; i < answers.size(); i++){
        auto edit = edits.at(i);
        edit->setText(answers.at(i));
        QString greenStyle = "background-color:rgb(178,217,177)";
        QString redStyle = "background-color:rgba(0, 255, 0, 0)";
        if(items.at(i).second == answers.at(i)){
            edit->setStyleSheet(greenStyle);
        }
        else{
            //edit->setStyleSheet(redStyle);
        }
    }
}
