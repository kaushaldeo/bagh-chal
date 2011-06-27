/**
* BoxWidget class
* @file BoxWidget.cpp
* @brief Implementation for BoxWidget Class
* @see BoxWidget
* @author Simon Schneeberger
*/

#include <QtGui>

#include "BaghChal.h"
#include "BoxWidget.h"
#include "../logic/Game.h"

using namespace baghchal;

BoxWidget::BoxWidget(QWidget *parent) :
    QWidget(parent)
{
    this->cell = NULL;
}

Cell *BoxWidget::getCell()
{
    if (this->cell == NULL)
    {
        this->cell = Game::getInstance()->getGrid().getCell(this->property("positionX").toInt(), this->property("positionY").toInt());
    }

    return this->cell;
}

void BoxWidget::setCell(Cell *cell)
{
    this->cell = cell;
}

void BoxWidget::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata"))
    {
        event->setAccepted(true);
        this->setAutoFillBackground(true);
        QPalette p(this->palette());
        p.setColor(QPalette::Background, QColor(147, 152, 170, 255));
        this->setPalette(p);
    }
    else
    {
        event->setAccepted(false);
    }
}

void BoxWidget::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata"))
    {
        event->setAccepted(true);
    }
    else
    {
        event->setAccepted(false);
    }
}

void BoxWidget::dragLeaveEvent(QDragLeaveEvent *event)
{
    Q_UNUSED(event);
    this->setAutoFillBackground(false);
}

void BoxWidget::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata"))
    {
        //delete hover effect
        this->setAutoFillBackground(false);

        AvatarWidget *srcAvatar = qobject_cast<AvatarWidget *>(event->source());

        if (srcAvatar)
        {
            //call the action handler
            if (this->handleGameAction(srcAvatar))
            {
                //set the source-box droppable again
                srcAvatar->parentWidget()->setAcceptDrops(1);

                //drop the avatar
                placeAvatar();

                //notify players who is next
                if (Game::getInstance()->getTurn() != empty)
                {
                    if (srcAvatar->property("goat").toBool())
                    {
                        BaghChal::getInstance()->showTurnArrowAndMessage(tiger);
                    }
                    else
                    {
                        BaghChal::getInstance()->showTurnArrowAndMessage(goat);
                    }
                }

                event->setDropAction(Qt::MoveAction);
                event->setAccepted(true);
            }
            else
            {
                event->setDropAction(Qt::IgnoreAction);
                event->setAccepted(false);
            }
        }
        else
        {
            event->setDropAction(Qt::IgnoreAction);
            event->setAccepted(false);
        }
    }
    else
    {
        event->setDropAction(Qt::IgnoreAction);
        event->setAccepted(false);
    }
}

bool BoxWidget::handleGameAction(AvatarWidget *avatar)
{
    //destination cell is the droppable box
    Cell *dst = this->getCell();

    //source cell has to be found out now, the source cell could be out of the grid
    Cell *src;
    //check if the source cell is in grid via the position properties. Outer boxes haven't position properties.
    QWidget *srcWidget = avatar->parentWidget();
    BoxWidget *srcBoxWidget;

    if (srcWidget->property("positionX").isValid() && srcWidget->property("positionY").isValid())
    {
        srcBoxWidget = qobject_cast<BoxWidget *>(srcWidget);
        src = srcBoxWidget->getCell();
    }
    else
    {
        srcBoxWidget = NULL;
        src = NULL;
    }

    //handle actions for the goat
    if (avatar->property("goat").toBool())
    {
        try
        {
            //move goat from source to destination
            Game::getInstance()->getGoat().move(src, dst);
        }
        catch (CanNotMoveException *e)
        {
            BaghChal::getInstance()->showMessage(OnlyStatusBar, QString::fromUtf8(e->what()));
            return false;
        }
        catch (MustEatException *e)
        {
            BaghChal::getInstance()->showMessage(OnlyStatusBar, QString::fromUtf8(e->what()));
            return false;
        }
        catch (GoatWonException *e)
        {
            //goat has won, notify the goat player
            BaghChal::getInstance()->showMessage(NotificationWithoutTimer, QString::fromUtf8(e->what()));
        }
        catch (UnoccupiedCellException *e)
        {
            BaghChal::getInstance()->showMessage(OnlyStatusBar, QString::fromUtf8(e->what()));
            return false;
        }
        catch (InvalidOccupantException *e)
        {
            BaghChal::getInstance()->showMessage(OnlyStatusBar, QString::fromUtf8(e->what()));
            return false;
        }
    }
    //handle actions for the tiger
    else
    {
        try
        {
            //move tiger from source to destination
            Game::getInstance()->getTiger().move(src, dst);
        }
        catch (CanNotMoveException *e)
        {
            BaghChal::getInstance()->showMessage(OnlyStatusBar, QString::fromUtf8(e->what()));
            return false;
        }
        catch (MustEatException *e)
        {
            BaghChal::getInstance()->showMessage(OnlyStatusBar, QString::fromUtf8(e->what()));
            return false;
        }
        catch (TigerEatGoatException *e)
        {
            //remove goat from the box
            removeGoatFromBox(Game::getInstance()->getLastEatenGoatCell());

            //tiger has eaten a goat, place them in the rippedfield
            placeGoatInRippedField(Game::getInstance()->getTiger().getScore());

            BaghChal::getInstance()->showMessage(OnlyStatusBar, QString::fromUtf8(e->what()));
        }
        catch (TigerWonException *e)
        {
            //remove goat from the box
            removeGoatFromBox(Game::getInstance()->getLastEatenGoatCell());

            //tiger has eaten a goat, place them in the rippedfield
            placeGoatInRippedField(Game::getInstance()->getTiger().getScore());

            //notify tiger player if he has won
            BaghChal::getInstance()->showMessage(NotificationWithoutTimer, QString::fromUtf8(e->what()));
        }
        catch (GameEvenException *e)
        {
            //parity! this is a rare game event, but have to be notified
            BaghChal::getInstance()->showMessage(NotificationWithoutTimer, QString::fromUtf8(e->what()));
        }
        catch (UnoccupiedCellException *e)
        {
            BaghChal::getInstance()->showMessage(OnlyStatusBar, QString::fromUtf8(e->what()));
            return false;
        }
        catch (InvalidOccupantException *e)
        {
            BaghChal::getInstance()->showMessage(OnlyStatusBar, QString::fromUtf8(e->what()));
            return false;
        }
    }

    return true;
}

void BoxWidget::removeGoatFromBox(Cell *cell)
{
    int x = cell->getPosition().first;
    int y = cell->getPosition().second;

    QWidget *boxParent = this->parentWidget();
    QWidget *widget = qFindChild<QWidget *>(boxParent, "box_" + QString::number(y) + QString::number(x));

    if (widget)
    {
        //delete AvatarWidget and QLabel which is derived from QWidget
        foreach(QWidget * child, widget->findChildren<QWidget *>())
        {
            child->close();
        }
        widget->setAcceptDrops(1);
    }
}

void BoxWidget::placeGoatInRippedField(int score)
{
    QWidget *boxParent = this->parentWidget()->parentWidget();

    if (score >= 1 && score <= 5)
    {
        for (int i = 0; i < score; ++i)
        {
            //find the box element
            QWidget *rippedField = qFindChild<QWidget *>(boxParent, "rippedGoat_0" + QString::number(i));

            if (rippedField)
            {
                if (!rippedField->findChild<QLabel *>())
                {
                    //place a goat image in this box
                    QLabel *newIcong = new QLabel(rippedField);
                    newIcong->setGeometry(QRect(-3, 1, 41, 41));
                    newIcong->setPixmap(QPixmap(QString::fromUtf8(":/new/Files/icons/spielfigur_ziege.png")));
                    newIcong->show();
                }
            }
        }
    }
    //delete content of all ripped boxes
    else if (score == 0)
    {
        for (int i = 0; i < 5; ++i)
        {
            QWidget *rippedField = qFindChild<QWidget *>(boxParent, "rippedGoat_0" + QString::number(i));
            QLabel *label = rippedField->findChild<QLabel *>();

            if (label)
            {
                delete label;
            }
        }
    }
}

void BoxWidget::placeAvatar()
{
    QString name;
    QString imageName;
    QPixmap pixmap;

    if (getCell()->getStatus() == goat)
    {
        name = QString::fromUtf8("goat");
        imageName = QString::fromUtf8("goatImage");
        pixmap = QPixmap(QString::fromUtf8(":/new/Files/icons/spielfigur_ziege.png"));
    }
    else if (getCell()->getStatus() == tiger)
    {
        name = QString::fromUtf8("tiger");
        imageName = QString::fromUtf8("tigerImage");
        pixmap = QPixmap(QString::fromUtf8(":/new/Files/icons/spielfigur_tiger.png"));
    }
    else
    {
        return;
    }

    //create a new avatar
    AvatarWidget *avatar = new AvatarWidget(this);
    avatar->setObjectName(name);
    avatar->setGeometry(QRect(0, 0, 51, 51));

    if (getCell()->getStatus() == goat)
    {
        avatar->setProperty("goat", QVariant(true));
        avatar->move(QPoint(-2, -1));
    }
    else
    {
        avatar->setProperty("goat", QVariant(false));
        avatar->move(QPoint(-1, -1));
    }

    //create avatar image as QLabel
    QLabel *avatarImage = new QLabel(avatar);
    avatarImage->setObjectName(name);
    avatarImage->setGeometry(QRect(0, 0, 41, 41));
    avatarImage->setPixmap(pixmap);

    //show avatars
    avatar->show();
    avatarImage->show();

    //set this box undroppable
    this->setAcceptDrops(0);
}
