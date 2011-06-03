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
    setAttribute(Qt::WA_DeleteOnClose);
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
    
    //clean old avatars
    cleanAvatars();
    
    QLabel *child = this->findChild<QLabel *>();
    if (!child)
    {
        return;
    }

    //check if avatar can move
    if ( this->property("goat").toBool() )
    {
        if ( Game::getInstance()->getTurn() == tiger )
        {
            //notify player that he can't move now
            BaghChal::getInstance()->showMessage(NotificationWithTimer, QString::fromUtf8("Tiger ist an der Reihe."));
            event->setAccepted("false");
            return;
        }
    }
    else
    {
        if ( Game::getInstance()->getTurn() == goat )
        {
            //notify player that he can't move now
            BaghChal::getInstance()->showMessage(NotificationWithTimer, QString::fromUtf8("Ziege ist an der Reihe."));
            event->setAccepted("false");
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
    
    //if (drag->exec(Qt::MoveAction) == Qt::MoveAction)
    if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction)
    {
        //do nothing yet, could be used for special actions if dropping is successful
    }
    else
    {  
        child->show();
    }
}

/**
 * @fn cleanAvatars()
 * @brief Clean Widgets in boxes
 * @see mousePressEvent
 * 
 * Source Avatars and Images needs to be closed when dropping to a new box.
 * This couldn't be done in the dropEvent cause of segmentation fault in Qt event functions.
 */
void AvatarWidget::cleanAvatars()
{
    list<BoxWidget*> boxes = BaghChal::getInstance()->getBoxes();
    list<BoxWidget*>::iterator it;

    for( it = boxes.begin(); it != boxes.end(); ++it )
    {
        Cell *cell = (*it)->getCell();
        if ( cell->getStatus() == empty  )
        {
            foreach(QWidget *widget, (*it)->findChildren<QWidget*>())
            {
                widget->close();
            }
        }
    }
}
