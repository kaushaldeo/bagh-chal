/**
 * @file Tiger.cpp
 * @brief Implementation of Tiger Class
 * @author Steffen Dittmar
 */

#include "Tiger.h"

Tiger::Tiger(Cell *cell)
{
    cellPtr = cell;
}

bool Tiger::canMove()
{
    for(int i = 0; i < 8; i++)
    {
		Cell *temp; 
        try
        {
            temp = cellPtr->getNeighbor((Direction) i);
        }
        catch(CanNotMoveException e)
        {
            continue;
        }

        if(temp->getStatus() == empty)
        {
            return true;
        }
        else if(temp->getStatus() == goat)
        {
			Cell *nextTemp;
            try
            {
                nextTemp = temp->getNeighbor((Direction) i);
            }
            catch(CanNotMoveException e)
            {
                continue;
            }

            if(nextTemp->getStatus() == empty)
            {
                return true;
            }
        }
    }
    
    return false;
}

bool Tiger::canMoveThere(Cell *cell)
{
	if(cell->getStatus() == tiger)
	{
		return false;
	}

	Direction dir;

	try
	{
		dir = cellPtr->isNeighbor(cell);
	}
	catch(InvalidDirectionException e)
	{
		return false;
	}

	if(cell->getStatus() == empty)
	{
		return true;
	}
	else if(cell->getStatus() == goat)
	{
		Cell *targetCell;

		try
		{
			targetCell = cell->getNeighbor(dir);
		}
		catch(CanNotMoveException e)
		{
			return false;
		}

		if(targetCell->getStatus() == empty)
		{
			return true;
		}

		return false;
	}

	return false;
}


int Tiger::move(Cell *cell)
{
	/*
	 * Warning, move doesn't do any reliable exception handling anymore,
	 * never call without calling canMoveThere first.
	 */

	if(cell->getStatus() == empty)
	{
                cellPtr->removeTiger();
		cellPtr = cell;
		cellPtr->setTiger(this);
		return 0;
	}
	else if(cell->getStatus() == goat)
	{
		Direction dir;

		try
		{
			dir = cellPtr->isNeighbor(cell);
		}
		catch(InvalidDirectionException e)
		{
			throw new CanNotMoveException;
		}

		Cell *jumpOverCell = cell;
		cell = cell->getNeighbor(dir);
		
                cellPtr->removeTiger();
		jumpOverCell->getGoat()->setCell(NULL);
		jumpOverCell->removeGoat();
		cellPtr = cell;
		cellPtr->setTiger(this);
		return 1;
	}

	throw new CanNotMoveException();


}

void Tiger::setCell(Cell *cell)
{
	cellPtr = cell;
}

Cell* Tiger::getCell()
{
	return cellPtr;
}
