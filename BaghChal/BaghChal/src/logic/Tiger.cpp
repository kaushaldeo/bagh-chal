/**
 * @file Tiger.cpp
 * @brief Implementation of Tiger Class
 * @author Steffen Dittmar
 */

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
	Direction dir;

	try
	{
		dir = cellPtr->isNeighbor(cell);

		if(cell->getStatus() == empty)
		{
			return true;
		}

		return false;
	}
	catch(InvalidDirectionException e)
	{
		try
		{
			dir = cellPtr->isJumpOverNeighbor(cell);
			if(cell->getStatus() == empty)
			{
				return true;
			}

			return false;
		}
		catch(InvalidDirectionException e)
		{
			return false;
		}
	}


	return false;
}


int Tiger::move(Cell *cell)
{
	/*
	 * Warning, move doesn't do any reliable exception handling anymore,
	 * never call without calling canMoveThere first.
	 */

	Direction dir;

	try
	{
		dir = cellPtr->isNeighbor(cell);

		if(cell->getStatus() == empty)
		{
			cellPtr->removeTiger();
			cellPtr->setStatus(empty);
			cellPtr = cell;
			cellPtr->setTiger(this);
			cellPtr->setStatus(tiger);
			return 0;
		}
	}
	catch(InvalidDirectionException e)
	{
		try
		{
			dir = cellPtr->isJumpOverNeighbor(cell);

			Cell *jumpOverCell = cell->getNeighbor(dir);
			
			cellPtr->removeTiger();
			jumpOverCell->getGoat()->setCell(NULL);
			jumpOverCell->removeGoat();
			cellPtr = cell;
			cellPtr->setTiger(this);
			cellPtr->setStatus(tiger);
			return 1;

		}
		catch(InvalidDirectionException e)
		{
			throw new CanNotMoveException();
		}


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
