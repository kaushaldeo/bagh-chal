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
