/**
 * @file Goat.cpp
 * @brief Implementation file for Goat Class
 * @author Steffen Dittmar
 */

#include "Goat.h"

Goat::Goat()
{
    cellPtr = NULL;
}

void Goat::setCell(Cell *cell)
{
    cellPtr = cell;
}

void Goat::removeCell()
{
    cellPtr = NULL;
}

Cell *Goat::getCell()
{
    return cellPtr;
}

bool Goat::canMove()
{
	//Goat has not been set or has already been eaten
    if (cellPtr == NULL)
    {
        return false;
    }

	//for every possible direction
    for (int i = 0; i < 8; i++)
    {
        Cell *temp;

        try
        {
            temp = cellPtr->getNeighbor((Direction) i);
        }
        catch (CanNotMoveException e)
        {
			//Goat can not move in direction i, proceed to the next direction
            continue;
        }

		//Goat can move in at least one direction
        if (temp->getStatus() == empty)
        {
            return true;
        }
    }

	//Goat can't move in any direction
    return false;
}

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
