#include "TestIniDialog.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include "Note.h"
TestIniDialog::TestIniDialog(NotesPtr p, QWidget* parent): QDialog (parent)
{
    total = 0;
    setResource(p);
    okButton = new QPushButton("ok", this);
    cancleButton = new QPushButton("cancle", this);
    QHBoxLayout* buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancleButton);

    numberLabel = new QLabel(this);
    numberLabel->setText(QString::fromLocal8Bit("数量:0"));
    quantitySlider = new QSlider;
    quantitySlider->setOrientation(Qt::Horizontal);
    quantitySlider->setMinimum(0);
    quantitySlider->setMaximum(100);
    quantitySlider->setSingleStep(10);
    QHBoxLayout* sliderLayout = new QHBoxLayout;
    sliderLayout->addWidget(quantitySlider);
    sliderLayout->addWidget(numberLabel);
    connect(quantitySlider, &QSlider::valueChanged, this, &TestIniDialog::updateNum);
    quantitySlider->setValue(100);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    int maxNum = data->size();
    for(auto i = 0; i <= maxNum-1; i++){
        QCheckBox* box = new QCheckBox(this);
        connect(box, &QCheckBox::clicked, this, &TestIniDialog::updateNum);
        boxs.append(box);
        QString name = data->at(i)->meta.name;
        box->setText(name);
        mainLayout->addWidget(box);
    }
    mainLayout->addLayout(sliderLayout);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);
    connect(okButton, &QPushButton::clicked, this, &TestIniDialog::accept);
    connect(cancleButton, &QPushButton::clicked, this, &TestIniDialog::reject);
}

void TestIniDialog::setResource(NotesPtr p){
    assert(p != nullptr);
    data = p;
}

void TestIniDialog::updateNum(){
    int num = 0;
    if(boxs.size() == 0){
        numberLabel->setText("0");
        return;
    }
    for(int i = 0; i<=data->size()-1; i++){
        auto box = boxs.at(i);
        if(box->isChecked()){
            num += data->at(i)->items.size();
        }
    }
    total = num*1.0*quantitySlider->value()/100;
    if(total==0){
        total = 1;
    }
    const QString str(QString::number(total));
    numberLabel->setText(str);
}

QVector<int> TestIniDialog::choiceIndex(){
    QVector<int> indexs;
    for(int i = 0; i<=boxs.size()-1; i++){
        if(boxs.at(i)->isChecked()){
            indexs.push_back(i);
        }
    }
    return indexs;
}

int TestIniDialog::totalNum(){
    return total;
}
