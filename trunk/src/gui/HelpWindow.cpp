/**
 * HelpWindow class
 * @file HelpWindow.cpp
 * @brief Implementation for HelpWindow Class
 * @see HelpWindow
 * @author Mirko Indlekofer
 */

#include "HelpWindow.h"

HelpWindow::HelpWindow(QWidget *parent) :
    QWidget(parent)
{
    //set up the popup window
    setupUi(this);
    
    //close the window
    connect(closeWindow, SIGNAL(clicked()), this, SLOT(close()));
}

HelpWindow::~HelpWindow() {}
