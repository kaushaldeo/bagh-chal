/**
* AvatarWidget class
* @file AvatarWidget.cpp
* @brief Implementation for AvatarWidget Class
* @see AvatarWidget
* @author Simon Schneeberger
*/
#include <QtGui>
#include <iostream>

#include "avatarWidget.h"
#include "BaghChal.h"
#include "../logic/Game.h"

using namespace std;
using namespace baghchal;

/**
 * @fn AvatarWidget()
 * @brief Constructor
 * @param parent - The parent QWidget element
 * 
 * Standard Constructor of AvatarWidget.
 */
AvatarWidget::AvatarWidget(QWidget *parent) :
    QWidget(parent)
{
}

/**
 * @fn mousePressEvent()
 * @brief The mouse press event from Qt
 * @param event - QMouseEvent value
 * 
 * If a mouse is pressed on an avatar check wether the avatar is moveable or not via the logic layer.
 * If it is moveable, create a drag object.
 */
void AvatarWidget::mousePressEvent(QMouseEvent *event)
{
    QLabel *child = this->findChild<QLabel *>();
    if (!child)
    {
        return;
    }

    //check if avatar can move
    if ( this->property("goat").toBool() )
    {
        if ( !Game::getInstance()->getGoat().canMove() )
        {
            //notify player that he can't move now
            BaghChal::getInstance()->setTurnNotification(tiger);
            return;
        }
    }
    else
    {
        if ( !Game::getInstance()->getTiger().canMove() )
        {
            //notify player that he can't move now
            BaghChal::getInstance()->setTurnNotification(goat);
            return;
        }
    }
    
    //create a new drag object
    QPoint *p = new QPoint(0, 2);
    
    QPixmap pixmap = *child->pixmap();
    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << pixmap << QPoint(event->pos());
    
    QMimeData *mimeData = new QMimeData;
    mimeData->setData("application/x-dnditemdata", itemData);
    
    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(pixmap);
    drag->setHotSpot(event->pos() - *p);
    child->hide();
    
    if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction)
    {
        event->ignore();
    }
    else
    {  
        child->show();
        child->setPixmap(pixmap);
    }
}
