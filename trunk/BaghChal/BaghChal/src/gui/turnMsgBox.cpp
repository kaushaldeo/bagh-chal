#include "turnMsgBox.h"

TurnMsgBox::TurnMsgBox(QWidget *parent) :
    QWidget(parent)
{}

void TurnMsgBox::mousePressEvent(QMouseEvent *event)
{
    (void) event;
    emit clicked();
}


