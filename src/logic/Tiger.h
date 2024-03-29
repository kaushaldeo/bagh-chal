/** @file Tiger.h
 *  @brief Headerfile for Tiger Class
 *  @author Steffen Dittmar
 */
#ifndef TIGER_H
#define TIGER_H

#include "Cell.h"
#include "Enums.h"
#include "Exceptions.h"
#include "Goat.h"

/**
* @class Tiger
* @brief Class of a single tiger
*
* This class is representing a single tiger in the logic layer.
*/
class Tiger
{
public:
    /**
     * @fn Tiger(Cell *cell)
     * @brief Overloaded constructor for class Tiger
     * @param cell - Cell this Tiger should be placed on
     *
     * Sets tiger on and registers it in cell.
     */
    Tiger(Cell *cell);

    /**
     * @fn canMove()
     * @brief Checks if this tiger can make any valid moves
     * @return True if a valid move is possible, else false
     */
    bool canMove();

    /**
     * @fn canMoveThere(Cell *cell)
     * @brief Checks if a move to a certain cell would be possible
     * @param cell - The cell to check if a valid move to would be possible
     * @return True if a move would be valid, else false
     */
    bool canMoveThere(Cell *cell);

    /**
     * @fn move(Cell *cell, bool mustEat)
     * @brief Moves the tiger to the cell passed as argument
     * @param cell - The cell to move the Tiger to
     * @param mustEat - A boolean value if the tiger has to eat a goat or not
     * @exception CanNotMoveException is thrown when a valid move to cell is not possible
     *
     * Checks if a valid move would be possible, then moves the tiger. Updates the affected cells.
     */
    int move(Cell *cell, bool mustEat);

    /**
     * @fn *getCell()
     * @brief Getter for cellPtr
     * @return The cell to set tiger on
     *
     * Only sets cellPtr to cell, doesnt register tiger in cell.
     */
    Cell *getCell();

    /**
     * @fn setCell(Cell *cell)
     * @brief Setter for cellPtr
     * @param cell - The cell to set tiger on
     *
     * Only sets cellPtr to cell, doesnt register tiger in cell.
     */
    void setCell(Cell *cell);

    /**
     * @fn couldEat()
     * @brief Cecks if this tiger could eat a goat
     * @return True if tiger could eat a goat, else false
     */
    bool couldEat();

private:
    Cell *cellPtr;			/**< Pointer to the Cell the tiger resides on */
};

#endif
