#include <QtGui>
#include <iostream>

#include "boxWidget.h"
#include "avatarWidget.h"
#include "BaghChal.h"
#include "../logic/Game.h"
#include "../logic/Cell.h"

using namespace std;


BoxWidget::BoxWidget(QWidget *parent) :
    QWidget(parent)
{
    /*Cell* cell = new Cell();
    Cell (int x, int y, Grid* gridPtr) : status (empty), positionX(x), positionY(y), grid(gridPtr), tigerPtr(0), goatPtr (0) {};
*/
}

void BoxWidget::dragEnterEvent(QDragEnterEvent *event)
{    
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
            this->setAutoFillBackground( true );
            QPalette p(this->palette());
            p.setColor(QPalette::Background, QColor(147,152,170,255));
            this->setPalette(p);
        }
    }
    else
    {
        event->ignore();
    }
}

void BoxWidget::dragMoveEvent(QDragMoveEvent *event)
{
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

void BoxWidget::dragLeaveEvent(QDragLeaveEvent *event)
{
    event->accept();
    this->setAutoFillBackground( false);
}

void BoxWidget::dropEvent(QDropEvent *event)
{

    if (event->mimeData()->hasFormat("application/x-dnditemdata"))
    {
        //delete hover effect
        this->setAutoFillBackground( false);

        AvatarWidget* avatar = qobject_cast<AvatarWidget*>(event->source());
        if ( avatar )
        {

            if ( avatar->property("goat").toBool() )
            {
                BaghChal::getInstance()->setStatusMsg(QString::fromUtf8("Tiger ist an der Reihe."));
            }
            else
            {
                BaghChal::getInstance()->setStatusMsg(QString::fromUtf8("Ziege ist an der Reihe."));
            }
            
            
            
            
            //this is a prototype
            placeGoatInRippedField();
            
            this->setAcceptDrops(0);
            avatar->parentWidget()->setAcceptDrops(1);
         
            AvatarWidget *newAvatar = new AvatarWidget(this);
            newAvatar->setObjectName(event->source()->objectName());
            newAvatar->setGeometry(QRect(0, 0, 51, 51));
            if ( avatar->property("goat").toBool() )
            {
                newAvatar->setProperty("goat",1);
                //newAvatar->setAttribute(Qt::WA_DeleteOnClose);
                //this is a little finetuning, could be solved via qt-designer
                newAvatar->move(QPoint(-3,2));
                Game::getInstance()->setTurn(tiger);
            }
            else
            {
                newAvatar->move(QPoint(-1,-1));
                Game::getInstance()->setTurn(goat);
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
            event->acceptProposedAction();
            event->source()->close();
        }
    }
    else
    {
        event->ignore();
    }
}

void BoxWidget::placeGoatInRippedField()
{
    //TODO: replace eatenGoats
    static int eatenGoats = 0;
    
    if ( eatenGoats >= 0 && eatenGoats < 5 )
    {
        QString rippedId = "";
        switch (eatenGoats)
        {
        case 0:
            rippedId = "rippedGoat_00";
            break;
        case 1:
            rippedId = "rippedGoat_01";
            break;
        case 2:
            rippedId = "rippedGoat_02";
            break;
        case 3:
            rippedId = "rippedGoat_03";
            break;
        case 4:
            rippedId = "rippedGoat_04";
        default:
            break;
        }
        
        QWidget *boxParent = this->parentWidget()->parentWidget();
        QWidget *rippedField = boxParent->findChild<QWidget*>(rippedId);
        if ( rippedField )
        {
            //TODO: replace eatenGoats
            eatenGoats++;
            
            QLabel *newIcong = new QLabel( rippedField );
            newIcong->setGeometry(QRect(-3, 1, 41, 41));
            newIcong->setPixmap(QPixmap(QString::fromUtf8(":/new/Files/icons/spielfigur_ziege.png")));
            newIcong->show();
        }
    }
}
