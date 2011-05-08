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
            temp = cellPtr->getNeighbor(i);
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
			Cell *nextTemp;
            try
            {
                nextTemp = temp->getNeighbor(i);
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




int Tiger::move(Cell *cell)
{
	if(cell->getStatus == tiger)
	{
		throw new CanNotMoveException;
	}

	Direction dir;

	try
	{
		dir = cellPtr->isNeighbor(cell);
	}
	catch(InvalidDirectionException e)
	{
		throw new CanNotMoveException;
	}

	if(cell->getStatus == empty)
	{
		cellPtr->removeTiger();
		cellPtr = cell;
		cellPtr->setTiger(this);
		return 0;
	}
	else if(cell->getStatus == goat)
	{
		Cell *jumpOverCell = cell;
		cell = cell->getNeighbor(dir);
		
		cellPtr->removeTiger();
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
