
#include "helpWindow.h"

HelpWindow::HelpWindow(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
    connect(closeWindow, SIGNAL(clicked()), this, SLOT(close()));
}

HelpWindow::~HelpWindow(){}
