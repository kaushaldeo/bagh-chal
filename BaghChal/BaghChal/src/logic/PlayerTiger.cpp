/**
 * @file PlayerTiger.cpp
 * @brief Implementation of TigerPlayer Class
 * @author Steffen Dittmar
 */

#include "PlayerTiger.h"

PlayerTiger::PlayerTiger(Cell *tigerCells[])
{
    tigers = new Tiger[4];

    for(int i = 0; i < 4; i++)
    {
        tigers[i] = new Tiger[tigerCells[i]];
    }

    score = 0;
}

PlayerTiger::~PlayerTiger()
{
    for(int i = 0; i < 4; i++)
    {
        delete tigers[i];
    }

    delete[] tigers;
}

bool PlayerTiger::canMove()
{
    for(int i = 0; i < 4; i++)
    {
        if(tigers[i]->canMove())
            //at least one tiger can move
            return true;
    }

    //no tiger can move
    return false;
}

Cell* PlayerTiger::move(Cell *src, Cell *dst)
{
    int i = 0;
    while(src != tigers[i]->getCell())
    {
        if(i >= 3)
            //no tiger resides on src
            throw InvalidSourceException;

        i++;
    }

    return tigers[i]->move(dst);
}

    
