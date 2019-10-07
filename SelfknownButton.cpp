#include "SelfknownButton.h"

SelfknownButton::SelfknownButton(QWidget* parent):QPushButton (parent)
{

    connect(this, &SelfknownButton::clicked, this, &SelfknownButton::clickedSlot);
}

void SelfknownButton::clickedSlot(){
    emit beClicked(this);
}
