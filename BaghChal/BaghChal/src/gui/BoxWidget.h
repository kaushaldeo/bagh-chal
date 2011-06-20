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
#include "AvatarWidget.h"

class QDragEnterEvent;
class QDropEvent;
class QDragMoveEvent;
class QDragLeaveEvent;

/**
* @class BoxWidget
* @brief This is a derived class from QWidget which represents a cell in the playing field
*
* The BoxWidget class represents a single field called box on the playing field as a derived class from QWidget.
* The class places an avatar and communicates with the underlying logic layer.
*/
class BoxWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BoxWidget(QWidget *parent = 0);       /**< Constructor */
    Cell *getCell();                               /**< Getter for a cell */
    void setCell(Cell *cell);                      /**< Setter for a cell */
    void placeAvatar();                            /**< Place an avatar in a field */
    void placeGoatInRippedField(int eatenGoats);   /**< Place an eaten goat in the ripped field */

protected:
    void dragEnterEvent(QDragEnterEvent *event);   /**< Overloaded Qt dragEnterEvent function */
    void dropEvent(QDropEvent *event);             /**< Overloaded Qt dropEvent function */
    void dragMoveEvent(QDragMoveEvent *event);     /**< Overloaded Qt dragMoveEvent function */
    void dragLeaveEvent(QDragLeaveEvent *event);   /**< Overloaded Qt dragLeaveEvent function */

private:
    bool handleGameAction(AvatarWidget *avatar);   /**< Communicate with the logic layer */
    void removeGoatFromBox(Cell *cell);            /**< Remove a goat from a single field in the grid, needed for eating a goat */
    Cell *cell;

};

#endif // BOXWIDGET_H
