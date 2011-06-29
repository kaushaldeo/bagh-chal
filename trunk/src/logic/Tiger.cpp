/**
 * @file Tiger.cpp
 * @brief Implementation of Tiger Class
 * @author Simon Schneeberger
 */

#include "Game.h"
#include "Tiger.h"

using namespace baghchal;

Tiger::Tiger(Cell *cell)
{
    cellPtr = cell;
    cell->setTiger(this);
    cell->setStatus(tiger);
}

bool Tiger::canMove()
{
	//For every possible direction
    for (int i = 0; i < 8; i++)
    {
        Cell *temp;

        try
        {
            temp = cellPtr->getNeighbor((Direction) i);
        }
        catch (CanNotMoveException e)
        {
			//Tiger can not move in direction i, proceed to the next direction
            continue;
        }

        if (temp->getStatus() == empty)
        {
			//Tiger can move in at least one direction
            return true;
        }
        else if (temp->getStatus() == goat)
        {
			//Tiger could possibly eat a goat
            Cell *nextTemp;

            try
            {
                nextTemp = temp->getNeighbor((Direction) i);
            }
            catch (CanNotMoveException e)
            {
				//Tiger can not jump over the goat in direction i, proceed to next direction
                continue;
            }

            if (nextTemp->getStatus() == empty)
            {
				//Tiger can move in at least one direction
                return true;
            }
        }
    }

	//Tiger can't move in any direction
    return false;
}

bool Tiger::canMoveThere(Cell *cell)
{
    Direction dir;

    try
    {
        dir = cellPtr->isNeighbor(cell);

        if (cell->getStatus() == empty)
        {
			//Cell is next to cell the tiger resides on and is empty
            return true;
        }

		//Cell is next to the cell the tiger resides on, but is not empty
        return false;
    }
    catch (InvalidDirectionException e)
    {
		//Cell is not next to the cell the tiger resides on
        try
        {
            dir = cellPtr->isJumpOverNeighbor(cell);

            if (cell->getStatus() == empty)
            {
				//The cell next to the one this tiger resides on is occupied
				//by a goat and the cell next to it in the same direction is
				//empty
                return true;
            }

			//The cell next to the one this tiger resides on is occupied
			//by a goat, but the one next to it in the same direction is
			//not empty
            return false;
        }
        catch (InvalidDirectionException e)
        {
			//Cell is not next to a cell next to the cell the tiger resides on
            return false;
        }
    }

	//Paranoia
    return false;
}

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
			//Tiger is moved to an empty cell next to it's origin
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
			//Tiger is about to eat a goat
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
			//Dst is not next to this tigers current cell and not
			//next to the one next to it
            throw new CanNotMoveException();
        }


    }

	//Paranoia
    throw new CanNotMoveException();
}

void Tiger::setCell(Cell *cell)
{
    cellPtr = cell;
}

Cell *Tiger::getCell()
{
    return cellPtr;
}

bool Tiger::couldEat()
{
    Direction allDirections[8] = {baghchal::right, baghchal::below, baghchal::left, baghchal::above, baghchal::rightAbove, baghchal::rightBelow, baghchal::leftBelow, baghchal::leftAbove};

	//For every direction
    for (int i = 0; i < 8; ++i)
    {
        Cell *test;

        try
        {
			//Check if the cell next to the one this tiger currently
			//resides on contains a goat
            test = cellPtr->getNeighbor(allDirections[i]);

            if (test->getStatus() == baghchal::goat)
            {
                try
                {
					//Check if the cell next to the one containing the goat
					//in the same direction is empty
                    test = test->getNeighbor(allDirections[i]);

                    if (test->getStatus() == baghchal::empty)
                    {
                        return true;
                    }
                }
                catch (CanNotMoveException e)
                {
					//Goat can not be eaten, proceed to the next direction
                    continue;
                }
            }
        }
        catch (CanNotMoveException e)
        {
			//Tiger can not move in direction i, proceed to next direction
            continue;
        }
    }

	//No goat could be eaten
    return false;
}
