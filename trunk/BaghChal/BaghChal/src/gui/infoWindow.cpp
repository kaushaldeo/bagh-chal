/**
 * InfoWindow class
 * @file InfoWindow.cpp
 * @brief Implementation for InfoWindow Class
 * @see InfoWindow
 * @author Mirko Indlekofer
 */

#include "InfoWindow.h"

/**
 * @fn InfoWindow()
 * @brief Constructor
 * @param parent - The parent QWidget element
 *
 * After setting the parent of info window, this function sets up the info window.
 */
InfoWindow::InfoWindow(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
    connect(closeWindow, SIGNAL(clicked()), this, SLOT(close()));
}

/**
 * @fn ~InfoWindow()
 * @brief Destructor
 */
InfoWindow::~InfoWindow() {}
