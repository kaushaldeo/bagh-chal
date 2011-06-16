/**
 * HelpWindow class
 * @file HelpWindow.cpp
 * @brief Implementation for HelpWindow Class
 * @see HelpWindow
 * @author Mirko Indlekofer
 */

#include "helpWindow.h"

/**
 * @fn HelpWindow()
 * @brief Constructor
 * @param parent - The parent QWidget element
 *
 * After setting the parent of HelpWindow, this function sets up the Help Window.
 */
HelpWindow::HelpWindow(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
    connect(closeWindow, SIGNAL(clicked()), this, SLOT(close()));
}

/**
 * @fn ~HelpWindow()
 * @brief Destructor
 */
HelpWindow::~HelpWindow() {}
