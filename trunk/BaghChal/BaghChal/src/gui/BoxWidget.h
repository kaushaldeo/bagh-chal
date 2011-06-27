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
    /**
     * @fn BoxWidget()
     * @brief Constructor
     * @param parent - The parent QWidget element
     *
     * The function sets the parent of BoxWidget and cell to NULL
     */
    explicit BoxWidget(QWidget *parent = 0);   
    
    /**
     * @fn getCell()
     * @brief Set and returns cell
     * @param parent - The parent QWidget element
     * @return cell
     *
     * If no cell is set yet, retrieve the correspondending cell from the logic layer and set them to cell
     */
    Cell *getCell();

    /**
     * @fn setCell()
     * @brief Set cell
     * @param cell - Cell* value to set the cell
     * @see renderGame()
     */    
    void setCell(Cell *cell);  

    /**
     * @fn placeAvatar()
     * @brief Places a goat in a box
     * @see dropEvent()
     * @see renderGame()
     *
     * Places an avatar in a box in the playing field.
     */    
    void placeAvatar();      

    /**
     * @fn placeGoatInRippedField()
     * @brief Places an eaten goat in the ripped field
     * @param eatenGoats - int value
     * @see handleGameAction()
     * @see renderGame()
     *
     * Places an eaten goat in one of the ripped field out of the grid. Notify the tiger player if he has eaten 5 goats.
     * If score is 0 the method deletes all goat images, this is especially used for loading a new game.
     */    
    void placeGoatInRippedField(int eatenGoats);  

protected:
    /**
     * @fn dragEnterEvent()
     * @brief The drag start event from Qt
     * @param event - QDragEnterEvent value
     *
     * If a drag is started over the BoxWidget, hover the BoxWidget with a grey color.
     */
    void dragEnterEvent(QDragEnterEvent *event); 

    /**
     * @fn dropEvent()
     * @brief The drop event from Qt
     * @param event - QDropEvent value
     *
     * Checks wether the drop is allowed or not. If it is allowed drop the avatar.
     */    
    void dropEvent(QDropEvent *event);   

    /**
     * @fn dragMoveEvent()
     * @brief The drag move event from Qt
     * @param event - QDragMoveEvent value
     *
     * The standard drag move event.
     */    
    void dragMoveEvent(QDragMoveEvent *event);  
    
    /**
     * @fn dragLeaveEvent()
     * @brief The leave drag event from Qt
     * @param event - QDragLeaveEvent value
     *
     * Delete the hover effect.
     */    
    void dragLeaveEvent(QDragLeaveEvent *event);   

private:

    /**
     * @fn handleGameAction()
     * @brief The game handler
     * @param avatar - AvatarWidget value
     * @see dropEvent()
     * @return bool
     *
     * Checks wether the avatar can move or not via the logic layer. Moves the avatar from the source cell to the destination cell.
     * Catch exceptions thrown by the logic layer (e.g. the goat has won).
     */
    bool handleGameAction(AvatarWidget *avatar); 

    /**
     * @fn removeGoatFromBox()
     * @brief Removes an avatar from a box
     * @param Cell - The cell from which a goat has to be removed
     * @see handleGameAction()
     *
     * Removes a goat from a box. This is called if a goat is eaten by a tiger.
     */
    void removeGoatFromBox(Cell *cell);
    
    Cell *cell;

};

#endif // BOXWIDGET_H
