#include <QtGui>
#include <iostream>

#include "avatarWidget.h"

using namespace std;


AvatarWidget::AvatarWidget(QWidget *parent) :
    QWidget(parent)
{
}

void AvatarWidget::mousePressEvent(QMouseEvent *event)
{
    QLabel *child = this->findChild<QLabel *>();
    if (!child)
    {
        return;
    }
    
    setCursor(Qt::OpenHandCursor);
    
    QPoint *p = new QPoint(0, 6);
    
    QPixmap pixmap = *child->pixmap();
    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << pixmap << QPoint(event->pos() - *p);
    
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
