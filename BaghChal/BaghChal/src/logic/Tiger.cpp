/**
 * @file Tiger.cpp
 * @brief Implementation of Tiger Class
 * @author Steffen Dittmar
 */

#include "Game.h"
#include "Tiger.h"

using namespace baghchal;

/**
 * @brief Overloaded constructor for class Tiger
 * @param cell - Cell this Tiger should be placed on
 *
 * Sets tiger on and registers it in cell.
 */
Tiger::Tiger(Cell *cell)
{
    cellPtr = cell;
    cell->setTiger(this);
    cell->setStatus(tiger);
}

/**
 * @brief Checks if this tiger can make any valid moves
 * @return True if a valid move is possible, else false
 */
bool Tiger::canMove()
{
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
        else if (temp->getStatus() == goat)
        {
            Cell *nextTemp;

            try
            {
                nextTemp = temp->getNeighbor((Direction) i);
            }
            catch (CanNotMoveException e)
            {
                continue;
            }

            if (nextTemp->getStatus() == empty)
            {
                return true;
            }
        }
    }

    return false;
}

/**
 * @brief Checks if a move to a certain cell would be possible
 * @param cell - The cell to check if a valid move to would be possible
 * @return True if a move would be valid, else false
 */
bool Tiger::canMoveThere(Cell *cell)
{
    Direction dir;

    try
    {
        dir = cellPtr->isNeighbor(cell);

        if (cell->getStatus() == empty)
        {
            return true;
        }

        return false;
    }
    catch (InvalidDirectionException e)
    {
        try
        {
            dir = cellPtr->isJumpOverNeighbor(cell);

            if (cell->getStatus() == empty)
            {
                return true;
            }

            return false;
        }
        catch (InvalidDirectionException e)
        {
            return false;
        }
    }


    return false;
}

/**
 * @brief Moves the tiger to the cell passed as argument
 * @param cell - The cell to move the Tiger to
 * @exception CanNotMoveException is thrown when a valid move to cell is not possible
 *
 * Checks if a valid move would be possible, then moves the tiger. Updates the affected cells.
 */
int Tiger::move(Cell *cell, bool mustEat)
{
    if (!canMoveThere(cell))
    {
        throw new CanNotMoveException();
    }

    Direction dir;

    try
    {
        dir = cellPtr->isNeighbor(cell);

        if (cell->getStatus() == empty)
        {
            if (mustEat)
            {
                throw new MustEatException();
            }

            cellPtr->removeTiger();
            cellPtr->setStatus(empty);
            cellPtr = cell;
            cellPtr->setTiger(this);
            cellPtr->setStatus(tiger);
            return 0;
        }
    }
    catch (InvalidDirectionException e)
    {
        try
        {
            dir = cellPtr->isJumpOverNeighbor(cell);
            Cell *jumpOverCell = cellPtr->getNeighbor(dir);
            cellPtr->removeTiger();
            jumpOverCell->getGoat()->removeCell();
            jumpOverCell->removeGoat();
            Game::getInstance()->setLastEatenGoatCell(jumpOverCell);
            cellPtr = cell;
            cellPtr->setTiger(this);
            cellPtr->setStatus(tiger);
            return 1;
        }
        catch (InvalidDirectionException e)
        {
            throw new CanNotMoveException();
        }


    }

    throw new CanNotMoveException();
}

/**
 * @brief Setter for cellPtr
 * @param cell - The cell to set tiger on
 *
 * Only sets cellPtr to cell, doesnt register tiger in cell.
 */
void Tiger::setCell(Cell *cell)
{
    cellPtr = cell;
}

/**
 * @brief Getter for cellPtr
 * @return The cell to set tiger on
 *
 * Only sets cellPtr to cell, doesnt register tiger in cell.
 */
Cell *Tiger::getCell()
{
    return cellPtr;
}

/**
 * @brief Cecks if this tiger could eat a goat
 * @return True if tiger could eat a goat, else false
 */
bool Tiger::couldEat()
{
    Direction allDirections[8] = {baghchal::right, baghchal::below, baghchal::left, baghchal::above, baghchal::rightAbove, baghchal::rightBelow, baghchal::leftBelow, baghchal::leftAbove};

    for (int i = 0; i < 8; ++i)
    {
        Cell *test;

        try
        {
            test = cellPtr->getNeighbor(allDirections[i]);

            if (test->getStatus() == baghchal::goat)
            {
                try
                {
                    test = test->getNeighbor(allDirections[i]);

                    if (test->getStatus() == baghchal::empty)
                    {
                        return true;
                    }
                }
                catch (CanNotMoveException e)
                {
                    continue;
                }
            }
        }
        catch (CanNotMoveException e)
        {
            continue;
        }
    }

    return false;
}
