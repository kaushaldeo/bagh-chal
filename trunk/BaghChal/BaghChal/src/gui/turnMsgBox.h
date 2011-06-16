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
 * @brief Derived Class of QWidget for the Turn Message Box
 *
 * The TurnMsgBox Class is a message box, which tells the user whose turn is it. It also tells the user if a the game is over.
 */
class TurnMsgBox : public QWidget
{
    Q_OBJECT
public:
    explicit TurnMsgBox(QWidget *parent = 0);

protected:
    void mousePressEvent(QMouseEvent *event);  /**< Overloaded Qt mousePressEvent Funktion */

signals:
    void clicked();

public slots:

};

#endif // TURNMSGBOX_H
