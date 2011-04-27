#ifndef INFOWINDOW_H
#define INFOWINDOW_H

#include "../../ui_infoWindow.h"

#include <QWidget>

class InfoWindow : public QWidget, public Ui::infoPopup
{
    Q_OBJECT

public:
    explicit InfoWindow(QWidget *parent = 0);
    ~InfoWindow();

};

#endif // INFOWINDOW_H
