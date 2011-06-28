/** @file Goat.h
 *  @brief Headerfile for Goat Class
 *  @author Simon Schneeberger
 */
#ifndef GOAT_H
#define GOAT_H

#include "Cell.h"
#include "Exceptions.h"
#include "Enums.h"

/**
* @class Goat
* @brief Class of a single goat
*
* This class is representing a single goat in the logic layer.
*/
class Goat
{
public:
    /**
     * @fn Goat()
     * @brief Default constructor for class Goat
     *
     * Sets cellPtr to NULL, since a goat has to be placed manually.
     */
    Goat();

    /**
     * @fn setCell(Cell *cell)
     * @brief Setter for cellPtr
     * @param cell - The cell to set goat on
     *
     * Only sets cellPtr to cell, doesn't register goat in the cell.
     */
    void setCell(Cell *cell);

    /**
     * @fn removeCell()
     * @brief Set cellPtr to NULL
     *
     * Only sets cellPtr to NULL, doesn't unregister goat in the cell.
     */
    void removeCell();

    /**
     * @fn canMove()
     * @brief Checks if this goat can make any valid moves
     * @return True if a valid move is possible, else false
     *
     * Checks all neighboring cells and returns true on the first time it encounters an emty cell.
     */
    bool canMove();

    /**
     * @fn *getCell()
     * @brief Returns pointer to the Cell the goat resides on
     * @return Pointer to the cell which the goat resides on or NULL if the goat has not been set or
     *  has been removed
     */
    Cell *getCell();

    /**
     * @fn canMoveThere(Cell *cell)
     * @brief Checks if a move to a certain Cell would be possible
     * @param cell - Check the cell if a valid move to would be possible
     * @return True if a move would be valid, else false
     *
     * Checks if the cell which the goat resides on and the cell passed as parameter are next
     * to each other in the grid and if the destination cells status is empty.
     */
    bool canMoveThere(Cell *cell);

    /**
     * @fn move(Cell *cell)
     * @brief Moves the goat to the cell passed as argument
     * @param cell - The cell to move the goat to
     * @exception CanNotMoveException is thrown when a valid move to cell is not possible
     *
     * Checks if a valid move would be possible, then moves the goat. Updates the affected cells.
     */
    void move(Cell *cell);

private:
    Cell *cellPtr;			/**< Pointer to the cell the goat resides on */
};

#endif
