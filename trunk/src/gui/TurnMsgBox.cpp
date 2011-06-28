/**
 * TurnMsgBox class
 * @file TurnMsgBox.cpp
 * @brief Implementation for TurnMsgBox Class
 * @see TurnMsgBox
 * @author Mirko Indlekofer
 */

#include "TurnMsgBox.h"

TurnMsgBox::TurnMsgBox(QWidget *parent) :
    QWidget(parent)
{}

void TurnMsgBox::mousePressEvent(QMouseEvent *event)
{
    (void) event;
    emit clicked();
}


