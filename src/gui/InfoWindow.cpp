/**
 * InfoWindow class
 * @file InfoWindow.cpp
 * @brief Implementation for InfoWindow Class
 * @see InfoWindow
 * @author Mirko Indlekofer
 */

#include "InfoWindow.h"

InfoWindow::InfoWindow(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
    connect(closeWindow, SIGNAL(clicked()), this, SLOT(close()));
}

InfoWindow::~InfoWindow() {}
