#include <QtGui>
#include <iostream>

#include "avatarWidget.h"

using namespace std;


AvatarWidget::AvatarWidget(QWidget *parent) :
    QWidget(parent)
{
    setCursor(Qt::OpenHandCursor);
}

void AvatarWidget::mousePressEvent(QMouseEvent *event)
{
    QLabel *child = this->findChild<QLabel *>();
    if (!child)
    {
        return;
    }
      
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
    }
    else
    {  
        child->show();
        child->setPixmap(pixmap);
    }
}
