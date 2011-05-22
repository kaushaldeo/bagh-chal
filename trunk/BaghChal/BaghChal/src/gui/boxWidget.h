/**
* BoxWidget Class
* @file BoxWidget.h
* @brief Headerfile for BoxWidget Class
* @see BoxWidget
* @author Simon Schneeberger
*/
#ifndef BOXWIDGET_H
#define BOXWIDGET_H

#include <QWidget>
#include "../logic/Cell.h"
#include "avatarWidget.h"

class QDragEnterEvent;
class QDropEvent;
class QDragMoveEvent;
class QDragLeaveEvent;

/**
* @class BoxWidget
* @brief Derived Class from QWidget of a Cell in the playing field
* 
* The BoxWidget class represents a single field on the playing field as a derived class from QWidget. The class places an avatar and communicates with the underlying logic layer.
*/
class BoxWidget : public QWidget
{    
    Q_OBJECT

public:
    explicit BoxWidget(QWidget *parent = 0);
    Cell* getCell();
    void setCell(Cell *cell);
    void placeAvatar();
    void placeGoatInRippedField(int eatenGoats);  /**< Places an eaten goat in the ripped field */
    
protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dragLeaveEvent(QDragLeaveEvent *event);

private:
    bool handleGameAction(AvatarWidget* avatar);   /**< Communicates with the logic layer */
    Cell* cell;
signals:

public slots:
	
};

#endif // BOXWIDGET_H
