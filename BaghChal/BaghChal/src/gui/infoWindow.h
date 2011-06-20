/**
 * InfoWindow Class
 * @file InfoWindow.h
 * @brief Headerfile for InfoWindow Class
 * @see InfoWindow
 * @author Mirko Indlekofer
 */

#ifndef INFOWINDOW_H
#define INFOWINDOW_H

#include "../../ui_InfoWindow.h"

#include <QWidget>

/**
 * @class InfoWindow
 * @brief This is a derived class of QWidget for the info window
 *
 * The InfoWindow class represents the Info Window, which contains information about the program and their developers.
 */
class InfoWindow : public QWidget, public Ui::infoPopup
{
    Q_OBJECT

public:
    explicit InfoWindow(QWidget *parent = 0);
    ~InfoWindow();

};

#endif // INFOWINDOW_H
