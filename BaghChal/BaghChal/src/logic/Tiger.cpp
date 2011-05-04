/**
 * @file Tiger.cpp
 * @brief Implementation of Tiger Class
 * @author Steffen Dittmar
 */

#include "Tiger.h"
#include "Exceptions.h"

Tiger::Tiger(Cell *cell)
{
    cellPtr = cell;
}

bool Tiger::canMove()
{
    for(int i = 0; i < 8; i++)
    {
        try
        {
            Cell *temp = cellPtr->getNeighbour(i);
        }
        catch(CanNotMoveException e)
        {
            continue;
        }

        if(temp->getStatus == empty)
        {
            return true;
        }
        else if(temp->getStatus == goat)
        {
            try
            {
                Cell *nextTemp = temp->getNeighbour(i);
            }
            catch(CanNotMoveException e)
            {
                continue;
            }

            if(nextTemp->getStatus == empty)
            {
                return true;
            }
        }
    }
    
    return false;
}


}

Cell* move(Cell *cell)
{
	if(cell->getStatus == tiger)
	{
		throw new CanNotMoveException;
	}

	Direction dir = cellPtr->isNeighbour;

	if(cell->getStatus == empty)
	{
		cellPtr->removeTiger();
		cellPtr = cell;
		cellPtr->setTiger(this);
		return ;
	}
	else if(cell->getStatus == goat)
	{
		cell = cell->getNeighbour(dir);

		if(cell == NULL)
		{
			throw new CanNotMoveException e;
		}


}
