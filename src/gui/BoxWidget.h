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
* @brief This is a subclass of QWidget which represents a cell in the playing field (grid)
*
* The BoxWidget class represents a single field called box on the playing field as a subclass of QWidget.
* The class places an avatar and communicates with the underlying logic layer.
*/
class BoxWidget : public QWidget
{
    Q_OBJECT

public:
    /**
     * @fn BoxWidget(QWidget *parent = 0)
     * @brief Constructor
     * @param parent - The parent QWidget element
     *
     * The function sets the parent of BoxWidget and cell to NULL.
     */
    explicit BoxWidget(QWidget *parent = 0);   
    
    /**
     * @fn *getCell()
     * @brief Set and returns cell
     * @return cell
     * @see handleGameAction()
     *
     * If no cell is set yet, retrieve the correspondending cell in the grid from the logic layer and set them to the member cell.
     * This is used to check if a move is valid or not.
     */
    Cell *getCell();

    /**
     * @fn setCell(Cell *cell)
     * @brief Set cell
     * @param cell - Cell* value to set the cell
     * @see BaghChal::renderGame()
     */    
    void setCell(Cell *cell);  

    /**
     * @fn placeAvatar()
     * @brief Places a goat in a box
     * @see dropEvent()
     * @see BaghChal::renderGame()
     *
     * Places an avatar in a box in the playing field.
     */    
    void placeAvatar();      

    /**
     * @fn placeGoatInRippedField(int eatenGoats)
     * @brief Places an eaten goat in the ripped field
     * @param eatenGoats - int value
     * @see handleGameAction()
     * @see BaghChal::renderGame()
     *
     * Places an eaten goat in one of the ripped field out of the grid.
     * If score is 0 the method deletes all goat images, this is especially used for loading a new game.
     */    
    void placeGoatInRippedField(int eatenGoats);  

protected:
    /**
     * @fn dragEnterEvent(QDragEnterEvent *event)
     * @brief The drag start event from Qt
     * @param event - QDragEnterEvent value
     *
     * If a drag is started over the BoxWidget, hover the BoxWidget with a grey color.
     */
    void dragEnterEvent(QDragEnterEvent *event); 

    /**
     * @fn dropEvent(QDropEvent *event)
     * @brief The drop event from Qt
     * @param event - QDropEvent value
     *
     * Checks wether the drop is allowed or not. The real check is done in the handleGameAction() which is called here.
     * If it is allowed (true result from handleGameAction()), the method places the avatar on this box and sets the source box from which the avatar was dragged to droppable again.
     * Notify the Qt event if the move is allowed or not.
     */    
    void dropEvent(QDropEvent *event);   

    /**
     * @fn dragMoveEvent(QDragMoveEvent *event)
     * @brief The drag move event from Qt
     * @param event - QDragMoveEvent value
     *
     * The standard drag move event. This method checks the drag event of its correct mime type.
     */    
    void dragMoveEvent(QDragMoveEvent *event);  
    
    /**
     * @fn dragLeaveEvent(QDragLeaveEvent *event)
     * @brief The leave drag event from Qt
     * @param event - QDragLeaveEvent value
     *
     * Deletes the hover effect.
     */    
    void dragLeaveEvent(QDragLeaveEvent *event);   

private:

    /**
     * @fn handleGameAction(AvatarWidget *avatar)
     * @brief The game handler
     * @param avatar - AvatarWidget value
     * @see dropEvent()
     * @return bool
     *
     * Checks wether the avatar can move or not via the logic layer. Moves the avatar from the source cell to the destination cell and shows
     * an appropriate game message.
     * Catch exceptions thrown by the logic layer (e.g. the goat has won). Returns true if the move is allowed or false if the move is not allowed.
     */
    bool handleGameAction(AvatarWidget *avatar); 

    /**
     * @fn removeGoatFromBox(Cell *cell)
     * @brief Removes an avatar from a box
     * @param cell - The cell from which a goat has to be removed
     * @see handleGameAction()
     *
     * Removes a goat from a box. This is called if a goat is eaten by a tiger.
     */
    void removeGoatFromBox(Cell *cell);
    
    Cell *cell;             /**< Pointer to the correspondening cell of the grind in the logic layer */

};

#endif // BOXWIDGET_H
