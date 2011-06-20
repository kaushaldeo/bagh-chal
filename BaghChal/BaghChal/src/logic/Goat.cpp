/**
 * @file Game.cpp
 * @brief Implementation file for class Goat
 * @see Game.h
 */

#include "Goat.h"

/**
 * @brief Default constructor for class Goat
 *
 * Sets cellPtr to NULL, since a goat has to be placed manually.
 */
Goat::Goat()
{
    cellPtr = NULL;
}

/**
 * @brief Setter for cellPtr
 * @param cell - The cell to set goat on
 *
 * Only sets cellPtr to cell, doesn't register goat in the cell.
 */
void Goat::setCell(Cell *cell)
{
    cellPtr = cell;
}

/**
 * @brief Set cellPtr to NULL
 *
 * Only sets cellPtr to NULL, doesn't unregister goat in the cell.
 */
void Goat::removeCell()
{
    cellPtr = NULL;
}

/**
 * @brief Returns pointer to the Cell the goat resides on
 * @return Pointer to the cell which the goat resides on or NULL if the goat has not been set or
 *  has been removed
 */
Cell *Goat::getCell()
{
    return cellPtr;
}

/**
 * @brief Checks if this goat can make any valid moves
 * @return True if a valid move is possible, else false
 *
 * Checks all neighboring cells and returns true on the first time it encounters an emty cell.
 */
bool Goat::canMove()
{
    if (cellPtr == NULL)
    {
        return false;
    }

    for (int i = 0; i < 8; i++)
    {
        Cell *temp;

        try
        {
            temp = cellPtr->getNeighbor((Direction) i);
        }
        catch (CanNotMoveException e)
        {
            continue;
        }

        if (temp->getStatus() == empty)
        {
            return true;
        }
    }

    return false;
}

/**
 * @brief Checks if a move to a certain Cell would be possible
 * @param cell - Check the cell if a valid move to would be possible
 * @return True if a move would be valid, else false
 *
 * Checks if the cell which the goat resides on and the cell passed as parameter are next
 * to each other in the grid and if the destination cells status is empty.
 */
bool Goat::canMoveThere(Cell *cell)
{
    try
    {
        cellPtr->isNeighbor(cell);
    }
    catch (InvalidDirectionException e)
    {
        return false;
    }

    if (cell->getStatus() != empty)
    {
        return false;
    }

    return true;
}

/**
 * @brief Moves the goat to the cell passed as argument
 * @param cell - The cell to move the goat to
 * @exception CanNotMoveException is thrown when a valid move to cell is not possible
 *
 * Checks if a valid move would be possible, then moves the goat. Updates the affected cells.
 */
void Goat::move(Cell *cell)
{
    if (!canMoveThere(cell))
    {
        throw new CanNotMoveException();
    }

    cellPtr->removeGoat();
    cellPtr->setStatus(empty);
    cellPtr = cell;
    cellPtr->setGoat(this);
    cellPtr->setStatus(goat);
}
