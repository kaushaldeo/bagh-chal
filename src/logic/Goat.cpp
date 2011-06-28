/**
 * @file Goat.cpp
 * @brief Implementation file for Goat Class
 * @author Simon Schneeberger
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
