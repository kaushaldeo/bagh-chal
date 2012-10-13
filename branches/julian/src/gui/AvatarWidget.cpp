/**
* AvatarWidget class
* @file AvatarWidget.cpp
* @brief Implementation for AvatarWidget Class
* @see AvatarWidget
* @author Simon Schneeberger
*/
#include <QtGui>

#include "AvatarWidget.h"
#include "BaghChal.h"
#include "../logic/Game.h"

using namespace baghchal;

AvatarWidget::AvatarWidget(QWidget *parent) :
    QWidget(parent)
{
    setAttribute(Qt::WA_DeleteOnClose);
}

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
    if (this->property("goat").toBool())
    {
        if (Game::getInstance()->getTurn() == tiger)
        {
            //notify player that he can't move now
            BaghChal::getInstance()->showMessage(NotificationWithTimer, QString::fromUtf8("Tiger ist an der Reihe."));
            event->setAccepted("false");
            return;
        }
    }
    else
    {
        if (Game::getInstance()->getTurn() == goat)
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

    if (drag->exec(Qt::MoveAction) == Qt::IgnoreAction)
    {
        child->show();
    }
}

void AvatarWidget::cleanAvatars()
{
    list<BoxWidget *> boxes = BaghChal::getInstance()->getBoxes();
    list<BoxWidget *>::iterator it;

    for (it = boxes.begin(); it != boxes.end(); ++it)
    {
        Cell *cell = (*it)->getCell();

        if (cell->getStatus() == empty)
        {
            foreach(QWidget * widget, (*it)->findChildren<QWidget *>())
            {
                widget->close();
            }
        }
    }
}
