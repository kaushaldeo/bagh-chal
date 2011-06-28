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
    setupUi(this);
    connect(closeWindow, SIGNAL(clicked()), this, SLOT(close()));
}

HelpWindow::~HelpWindow() {}
