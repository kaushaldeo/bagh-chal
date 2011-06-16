/**
 * HelpWindow Class
 * @file HelpWindow.h
 * @brief Headerfile for HelpWindow Class
 * @see HelpWindow
 * @author Mirko Indlekofer
 */

#ifndef HELPWINDOW_H
#define HELPWINDOW_H

#include "../../ui_helpWindow.h"

#include <QWidget>

/**
 * @class HelpWindow
 * @brief Derived Class of QWidget for the Info Window
 *
 * The HelpWindow Class represents the Help Window, which contains the user manual and the rules of the game.
 */
class HelpWindow : public QWidget, public Ui::helpPopup
{
    Q_OBJECT

public:
    explicit HelpWindow(QWidget *parent = 0);
    ~HelpWindow();

};

#endif // HELPWINDOW_H
