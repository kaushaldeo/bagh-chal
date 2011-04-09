#include "BaghChal.h"
#include "../../ui_BaghChal.h"

BaghChal::BaghChal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BaghChal)
{
    ui->setupUi(this);
}

BaghChal::~BaghChal()
{
    delete ui;
}
