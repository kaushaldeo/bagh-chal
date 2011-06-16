#include "infoWindow.h"

InfoWindow::InfoWindow(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
    connect(closeWindow, SIGNAL(clicked()), this, SLOT(close()));
}

InfoWindow::~InfoWindow() {}
