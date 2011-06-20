/**
* AvatarWidget Class
* @file AvatarWidget.h
* @brief Headerfile for AvatarWidget Class
* @see AvatarWidget
* @author Simon Schneeberger
*/

#ifndef AVATARWIDGET_H
#define AVATARWIDGET_H

#include <QWidget>

class QMouseEvent;

/**
* @class AvatarWidget
* @brief This is a derived class from QWidget of an avatar
*
* The AvatarWidget class represents a player avatar goat or tiger
*/
class AvatarWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AvatarWidget(QWidget *parent = 0);  /**< Constructor */

protected:
    void mousePressEvent(QMouseEvent *event);    /**< Overloaded Qt mousePressEvent function */

private:
    void cleanAvatars();                         /**< Clean widgets in the fields */

};

#endif // AVATARWIDGET_H
