#include <QtGui>
#include <iostream>

#include "boxWidget.h"
#include "avatarWidget.h"


BoxWidget::BoxWidget(QWidget *parent) :
    QWidget(parent)
{
}

void BoxWidget::dragEnterEvent(QDragEnterEvent *event)
{
    setCursor(Qt::OpenHandCursor);
    
    if (event->mimeData()->hasFormat("application/x-dnditemdata"))
    {
        if (event->source() == this)
        {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        }
        else
        {
            event->acceptProposedAction();
        }
    }
    else
    {
        event->ignore();
    }
}

void BoxWidget::dragMoveEvent(QDragMoveEvent *event)
{
    setCursor(Qt::OpenHandCursor);
    
    if (event->mimeData()->hasFormat("application/x-dnditemdata"))
    {
        if (event->source() == this)
        {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        }
        else
        {
            event->acceptProposedAction();
        }
    }
    else
    {
        event->ignore();
    }
}

void BoxWidget::dropEvent(QDropEvent *event)
{

    if (event->mimeData()->hasFormat("application/x-dnditemdata"))
    {
        AvatarWidget* avatar = qobject_cast<AvatarWidget*>(event->source());
        if ( avatar )
        {
            this->setAcceptDrops(0);
            avatar->parentWidget()->setAcceptDrops(1);
         
            AvatarWidget *newAvatar = new AvatarWidget(this);
            //newAvatar->setObjectName(QString::fromUtf8("newAvatar"));
            newAvatar->setGeometry(QRect(0, 0, 51, 51));
            if ( avatar->property("goat").toBool() )
            {
                newAvatar->setProperty("goat",1);
                //this is a little finetuning, could be solved via qt-designer
                newAvatar->move(QPoint(-3,2));
            }
            else
            {
                newAvatar->move(QPoint(0,0));
            }
            newAvatar->show();
            
            QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
            QDataStream dataStream(&itemData, QIODevice::ReadOnly);
            
            QPixmap pixmap;
            QPoint offset;
            dataStream >> pixmap >> offset;
            
            QLabel *newIcon = new QLabel(newAvatar);
            newIcon->setPixmap(pixmap);
            newIcon->move(QPoint(0,0));
            newIcon->show();     
        }
           
        if (event->source() == this)
        {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        }
        else
        {
            event->acceptProposedAction();event->source()->close();
        }
    }
    else
    {
        event->ignore();
    }
}
