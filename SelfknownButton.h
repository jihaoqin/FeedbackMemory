#ifndef SELFKNOWNBUTTON_H
#define SELFKNOWNBUTTON_H

#include <QPushButton>

class SelfknownButton:public QPushButton
{
    Q_OBJECT
public:
    SelfknownButton(QWidget* parent = nullptr);
signals:
    void beClicked(SelfknownButton*);
public slots:
    void clickedSlot();
};

#endif // SELFKNOWNBUTTON_H
