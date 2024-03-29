/**
 * HelpWindow Class
 * @file HelpWindow.h
 * @brief Headerfile for HelpWindow Class
 * @see HelpWindow
 * @author Mirko Indlekofer
 */

#ifndef HELPWINDOW_H
#define HELPWINDOW_H

#include "../../ui_HelpWindow.h"

#include <QWidget>

/**
 * @class HelpWindow
 * @brief This is a derived class of QWidget for the help window
 *
 * The HelpWindow class represents the help window, which contains the user manual and the rules of the game.
 */
class HelpWindow : public QWidget, public Ui::helpPopup
{
    Q_OBJECT

public:
    /**
     * @fn HelpWindow(QWidget *parent = 0)
     * @brief Constructor
     * @param parent - The parent QWidget element
     *
     * After setting the parent of HelpWindow, this function sets up the help window.
     */
    explicit HelpWindow(QWidget *parent = 0);
    
    /**
     * @fn ~HelpWindow()
     * @brief Destructor
     */
    ~HelpWindow();

};

#endif // HELPWINDOW_H
