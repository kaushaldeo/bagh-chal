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
* The AvatarWidget class represents a player avatar of a goat or a tiger.
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
     * If a mouse is pressed on an avatar check wether the avatar is moveable or not. This is checked by the turn state of the game.
     * If it is moveable, create a drag object and hide the the object from which is dragged.
     * If the avatar is dropped to a cell (BoxWidget) the source object and drag object has to be closed and deleted.
     * If the avatar can not be dropped, the drag object will be destroyed and the source object will be shown again.
     */
    void mousePressEvent(QMouseEvent *event);    

private:
    /**
     * @fn cleanAvatars()
     * @brief Clean Widgets in boxes
     * @see mousePressEvent
     *
     * Avatars and images needs to be destroyed when dropping to a new cell (BoxWidget) was successfully.
     * Normally deleting old objects can be done at the end of Qt event handling, but this leads to a segmentation fault.
     * Therefore there is this clean method to delete unused objects on the grid, which is called by a click on an avatar.
     */
    void cleanAvatars();                      

};

#endif // AVATARWIDGET_H
