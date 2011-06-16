/**
 * InfoWindow Class
 * @file InfoWindow.h
 * @brief Headerfile for InfoWindow Class
 * @see InfoWindow
 * @author Mirko Indlekofer
 */

#ifndef INFOWINDOW_H
#define INFOWINDOW_H

#include "../../ui_infoWindow.h"

#include <QWidget>

/**
 * @class InfoWindow
 * @brief Derived Class of QWidget for the Info Window
 *
 * The InfoWindow Class represents the Info Window, which contains information about the program and their developers.
 */
class InfoWindow : public QWidget, public Ui::infoPopup
{
    Q_OBJECT

public:
    explicit InfoWindow(QWidget *parent = 0);
    ~InfoWindow();

};

#endif // INFOWINDOW_H
