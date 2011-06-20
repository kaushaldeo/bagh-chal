/**
 * TurnMsgBox class
 * @file TurnMsgBox.cpp
 * @brief Implementation for TurnMsgBox Class
 * @see TurnMsgBox
 * @author Mirko Indlekofer
 */

#include "TurnMsgBox.h"

/**
 * @fn TurnMsgBox()
 * @brief Constructor
 * @param parent - The parent QWidget element
 *
 * The function sets the parent of TurnMsgBox.
 */
TurnMsgBox::TurnMsgBox(QWidget *parent) :
    QWidget(parent)
{}

/**
 * @fn mousePressEvent()
 * @brief Overloaded Qt mousePressEvent Funktion
 * @param event - QMouseEvent value 
 * 
 * This function ignores the QMouseEvent parameter and emits an clicked signal.
 */
void TurnMsgBox::mousePressEvent(QMouseEvent *event)
{
    (void) event;
    emit clicked();
}


