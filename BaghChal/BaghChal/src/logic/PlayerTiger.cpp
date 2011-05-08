/**
 * @file PlayerTiger.cpp
 * @brief Implementation of TigerPlayer Class
 * @author Steffen Dittmar
 */

#include "PlayerTiger.h"

PlayerTiger::PlayerTiger(Cell *tigerCells[])
{
    tigers = new Tiger* [4];

    for(int i = 0; i < 4; i++)
    {
        tigers[i] = new Tiger(tigerCells[i]);
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

void PlayerTiger::move(Cell *src, Cell *dst)
{
	Tiger *thisTiger;
   	try
   	{
	   thisTiger = src->getTiger();
	}
	catch(exception e)
	{
		throw new CanNotMoveException();
	}

    int didScore = thisTiger->move(dst);

	if(didScore)
	{
		score++;
	}

}

int PlayerTiger::getScore()
{
	return score;
}

void PlayerTiger::setScore(int score)
{
	this->score = score;
}

void PlayerTiger::setTigers(Tiger **tigers)
{
	this->tigers = tigers;
}

Tiger** PlayerTiger::getTigers()
{
	return tigers;
}
    
