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
* @brief This is a subclass of QWidget and represents an avatar
*
* The AvatarWidget class represents a player avatar goat or tiger.
*/
class AvatarWidget : public QWidget
{
    Q_OBJECT
public:
   /**
    * @fn AvatarWidget(QWidget *parent = 0)
    * @brief Constructor
    * @param parent - The parent QWidget element
    *
    * Standard Constructor of AvatarWidget.
    */
    explicit AvatarWidget(QWidget *parent = 0);

protected:
    /**
     * @fn mousePressEvent(QMouseEvent *event)
     * @brief The mouse press event from Qt
     * @param event - QMouseEvent value
     *
     * If a mouse is pressed on an avatar check wether the avatar is moveable or not via the logic layer.
     * If it is moveable, create a drag object.
     */
    void mousePressEvent(QMouseEvent *event);    

private:
    /**
     * @fn cleanAvatars()
     * @brief Clean Widgets in boxes
     * @see mousePressEvent
     *
     * Old Avatars and images needs to be closed when dropping to a new box.
     * This couldn't be done in the dropEvent cause of segmentation fault in Qt event functions.
     */
    void cleanAvatars();                      

};

#endif // AVATARWIDGET_H
