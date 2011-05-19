#include <QtGui>
#include <iostream>

#include "boxWidget.h"
#include "BaghChal.h"
#include "../logic/Game.h"

using namespace std;
using namespace baghchal;


BoxWidget::BoxWidget(QWidget *parent) :
    QWidget(parent)
{
    this->cell = NULL;
}

Cell* BoxWidget::getCell()
{
    if ( this->cell == NULL )
    {
       this->cell = Game::getInstance()->getGrid().getCell( this->property("positionX").toInt(), this->property("positionY").toInt() );
    }
    return this->cell;
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
            if ( !this->handleGameAction( avatar ) )
            {
                event->ignore();
                return;
            }
                 
            this->setAcceptDrops(0);
            avatar->parentWidget()->setAcceptDrops(1);
         
            AvatarWidget *newAvatar = new AvatarWidget(this);
            newAvatar->setObjectName(event->source()->objectName());
            newAvatar->setGeometry(QRect(0, 0, 51, 51));
            if ( avatar->property("goat").toBool() )
            {
                newAvatar->setProperty("goat",1);
                //this is a little finetuning, could be solved via qt-designer
                newAvatar->move(QPoint(-3,2));
                
                BaghChal::getInstance()->showTurnArrowAndMessage(tiger);
            }
            else
            {
                //this is a little finetuning, could be solved via qt-designer
                newAvatar->move(QPoint(-1,-1));
                
                BaghChal::getInstance()->showTurnArrowAndMessage(goat);
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

bool BoxWidget::handleGameAction( AvatarWidget* avatar )
{
    Cell* dst = this->getCell();
    Cell* src;
    
    //check if box is in grid
    QWidget* srcWidget = avatar->parentWidget();
    if ( srcWidget->property("positionX").isValid() && srcWidget->property("positionY").isValid() )
    { 
        BoxWidget* srcBoxWidget = qobject_cast<BoxWidget*>(srcWidget);
        src = srcBoxWidget->getCell();
    }
    else
    {
        src = NULL;
    }
    
    if ( avatar->property("goat").toBool() )
    {
        if ( !Game::getInstance()->getGoat().canMoveThere(src, dst) )
        {
            return false;
        }
        
        try
        {
            Game::getInstance()->getGoat().move(src, dst);
        }
        catch( CanNotMoveException e )
        {
            return false;
        }
        catch( GoatWonException e )
        {
            BaghChal::getInstance()->setTurnNotification(3);
        }
    }
    else
    {
        if ( !Game::getInstance()->getTiger().canMoveThere(src, dst) )
        {
            return false;
        }
        
        try
        {
            Game::getInstance()->getTiger().move(src, dst);
        }
        catch( CanNotMoveException e)
        {
            return false;
        }
        catch( TigerEatGoatException e)
        {
            placeGoatInRippedField( Game::getInstance()->getTiger().getScore() );
        }
        catch( GameEvenException e)
        {
            //Parity!
            BaghChal::getInstance()->setTurnNotification(5);
        }
    }
    return true;
}


void BoxWidget::placeGoatInRippedField( int eatenGoats )
{  
    if ( eatenGoats >= 1 && eatenGoats <= 5 )
    {
        QString rippedId = "";
        switch (eatenGoats)
        {
        case 1:
            rippedId = "rippedGoat_00";
            break;
        case 2:
            rippedId = "rippedGoat_01";
            break;
        case 3:
            rippedId = "rippedGoat_02";
            break;
        case 4:
            rippedId = "rippedGoat_03";
            break;
        case 5:
            rippedId = "rippedGoat_04";
        default:
            break;
        }
        
        QWidget *boxParent = this->parentWidget()->parentWidget();
        QWidget *rippedField = boxParent->findChild<QWidget*>(rippedId);
        if ( rippedField )
        {            
            QLabel *newIcong = new QLabel( rippedField );
            newIcong->setGeometry(QRect(-3, 1, 41, 41));
            newIcong->setPixmap(QPixmap(QString::fromUtf8(":/new/Files/icons/spielfigur_ziege.png")));
            newIcong->show();
        }
        if ( eatenGoats == 5 )
        {
            BaghChal::getInstance()->setTurnNotification(4);
        }
    }
}

void BoxWidget::placeAvatar()
{
    QString name;
    QPixmap pixmap;

    if ( getCell()->getStatus() == goat )
    {
        name = QString::fromUtf8("goat");
        pixmap = QPixmap(QString::fromUtf8(":/new/Files/icons/spielfigur_ziege.png"));
    }
    else if ( getCell()->getStatus() == tiger )
    {
        name = QString::fromUtf8("tiger");
        pixmap = QPixmap(QString::fromUtf8(":/new/Files/icons/spielfigur_tiger.png"));
    }
    else
    {
        return;
    }

    QLabel* avatar = new QLabel(this);
    avatar->setObjectName(name);
    avatar->setGeometry(QRect(0, 0, 41, 41));
    avatar->setPixmap(pixmap);
}
