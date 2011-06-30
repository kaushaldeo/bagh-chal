/**
* Cell class
* @file Cell.cpp
* @brief Implementation for Cell Class
* @see Cell
* @author Julian Bayer
*/

#include "Cell.h"
#include "Exceptions.h"
#include "Goat.h"
#include "Tiger.h"


CellStatus Cell::getStatus()
{
    return status;
}

void Cell::setStatus(CellStatus newState)
{
    status = newState;
}

pair <int, int> Cell::getPosition()
{
    pair <int, int> pos;
    pos.first = positionX;
    pos.second = positionY;
    return pos;
}

Cell *Cell::getNeighbor(Direction direction)
{
    switch (direction)
    {
    case baghchal::right: //Right

        if (positionX == 4)     //Are we at the right edge of grid?
        {
            throw moveEx;
        }

        return grid->getCell(positionX + 1, positionY);

    case baghchal::below: //Down

        if (positionY == 4)     //Are we at the lower edge of grid?
        {
            throw moveEx;
        }

        return grid->getCell(positionX, positionY + 1);

    case baghchal::left: //Left

        if (positionX == 0)     //Are we at the left edge of grid?
        {
            throw moveEx;
        }

        return grid->getCell(positionX - 1, positionY);

    case baghchal::above: //Up

        if (positionY == 0)     //Are we at the upper edge of grid?
        {
            throw moveEx;
        }

        return grid->getCell(positionX, positionY - 1);

    case baghchal::rightAbove: //Right+Up

        if (positionX == 4  || positionY == 0 || !canMoveDiagonally())  //Are we in the upper right corner of grid or are we not allowed to move diagonally?
        {
            throw moveEx;
        }

        return grid->getCell(positionX + 1, positionY - 1);

    case baghchal::rightBelow: //Right+Down

        if (positionX == 4  || positionY == 4 || !canMoveDiagonally())  //Are we in the lower right corner of grid or are we not allowed to move diagonally?
        {
            throw moveEx;
        }

        return grid->getCell(positionX + 1, positionY + 1);

    case baghchal::leftBelow: //Left+Down

        if (positionX == 0  || positionY == 4 || !canMoveDiagonally())  //Are we in the lower left corner of grid or are we not allowed to move diagonally?
        {
            throw moveEx;
        }

        return grid->getCell(positionX - 1, positionY + 1);

    case baghchal::leftAbove: //Left+Up

        if (positionX == 0  || positionY == 0 || !canMoveDiagonally())  //Are we in the upper left corner of grid or are we not allowed to move diagonally?
        {
            throw moveEx;
        }

        return grid->getCell(positionX - 1, positionY - 1);
    default:
        return 0;
    }
}

bool Cell::canMoveDiagonally()
{
    return positionX % 2 == positionY % 2;  //If both the coordinates are odd, or both are even, we can move diagonally.
}

Tiger *Cell::getTiger()
{
    if (status == empty)
    {
        throw uOcEx;
    }
    else if (status == goat)
    {
        throw iOcEx;
    }

    return tigerPtr;
}

Goat *Cell::getGoat()
{
    if (status == empty)
    {
        throw uOcEx;
    }
    else if (status == tiger)
    {
        throw iOcEx;
    }

    return goatPtr;
}

void Cell::setTiger(Tiger *tiger)
{
    if (status != empty)
    {
        throw ocEx;
    }

    this->tigerPtr = tiger;
}

void Cell::overrideTiger(Tiger *tiger)
{
    this->tigerPtr = tiger;
}

void Cell::setGoat(Goat *goat)
{
    if (status != empty)
    {
        throw ocEx;
    }

    this->goatPtr = goat;
}

void Cell::overrideGoat(Goat *goat)
{
    this->goatPtr = goat;
}

void Cell::removeGoat()
{
    if (status == empty)
    {
        throw uOcEx;
    }

    if (status == tiger)
    {
        throw iOcEx;
    }

    goatPtr = 0;
    status = empty;
}

void Cell::removeTiger()
{
    if (status == empty)
    {
        throw uOcEx;
    }

    if (status == goat)
    {
        throw iOcEx;
    }

    tigerPtr = 0;
    status = empty;
}

Direction Cell::isNeighbor(Cell *cell)
{
    //Create array with all possible directions
    Direction allDirections[8] = {baghchal::right, baghchal::below, baghchal::left, baghchal::above, baghchal::rightAbove, baghchal::rightBelow, baghchal::leftBelow, baghchal::leftAbove};
    
    //For each direction...
    for (int i = 0; i < 8; i++)
    {
        try
        {
            //... get neighbor in that direction
            Cell *test = getNeighbor(allDirections[i]);

            //Is the cell we got the same as the cell we look for?
            if (test == cell)
            {
                return allDirections[i];    //If it is, return current direction
            }

            continue;   //If it is not, continue searching
        }
        catch (CanNotMoveException e)   //If we can't move in that direction, continue with next direction.
        {
            continue;
        }
    }

    throw InvalidDirectionException();  //If we haven't found the cell, it's not a neighbor and we throw this exception.
}

Direction Cell::isJumpOverNeighbor(Cell *cell)
{
    //Create array with all possible directions
    Direction allDirections[8] = {baghchal::right, baghchal::below, baghchal::left, baghchal::above, baghchal::rightAbove, baghchal::rightBelow, baghchal::leftBelow, baghchal::leftAbove};
    
    //For each direction...
    for (int i = 0; i < 8; i++)
    {
        try
        {
            //... get neighbor in that direction
            Cell *test = getNeighbor(allDirections[i]);

            if (test)
            {
                if (test->getStatus() == goat && test->getNeighbor(allDirections[i]) == cell)   //Is the neighboring cell occupoed by a goat and the next cell in this direction the cell we look for?
                {
                    return allDirections[i]; //Return current direction
                }
            }

            continue;   //If that's not the case, continue the search
        }
        catch (CanNotMoveException e)   //If we can't move in that direction, continue with next direction.
        {
            continue;
        }
    }

    throw InvalidDirectionException(); //If we haven't found the cell, it's not a jump-over-neighbor and we throw this exception.
}
