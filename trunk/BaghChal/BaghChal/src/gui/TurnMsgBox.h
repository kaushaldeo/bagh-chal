/**
 * TurnMsgBox Class
 * @file TurnMsgBox.h
 * @brief Headerfile for TurnMsgBox Class
 * @see TurnMsgBox
 * @author Mirko Indlekofer
 */

#ifndef TURNMSGBOX_H
#define TURNMSGBOX_H

#include <QWidget>

/**
 * @class TurnMsgBox
 * @brief This is a derived class of QWidget for the turn message box
 *
 * The TurnMsgBox class is a message box, which tells the user whose turn is it. It also tells the user when the game is over.
 */
class TurnMsgBox : public QWidget
{
    Q_OBJECT

public:
    /**
     * @fn TurnMsgBox()
     * @brief Constructor
     * @param parent - The parent QWidget element
     *
     * The function sets the parent of TurnMsgBox.
     */
    explicit TurnMsgBox(QWidget *parent = 0);

protected:
    /**
     * @fn mousePressEvent()
     * @brief Overloaded Qt mousePressEvent Funktion
     * @param event - QMouseEvent value 
     * 
     * This function ignores the QMouseEvent parameter and emits an clicked signal.
     */
    void mousePressEvent(QMouseEvent *event);  

signals:
    void clicked();

};

#endif // TURNMSGBOX_H
