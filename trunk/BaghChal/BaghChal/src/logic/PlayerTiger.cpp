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

PlayerTiger::PlayerTiger(Cell *tigerCells[], PlayerGoat *playerGoat)
{
	opponent = playerGoat;

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

bool PlayerTiger::canMoveThere(Cell *src, Cell *dst)
{
	/*
	 * Warning, move doesn't do any reliable exception handling anymore,
	 * never call without calling canMoveThere first.
	 */

	Tiger *thisTiger;

	try
	{
		thisTiger = src->getTiger();
	}
	catch(exception e)
	{
		return false;
	}

	return thisTiger->canMoveThere(dst);
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

	if(score == 5)
	{
		throw new TigerWonException();
	}

	if(!opponent->canMove())
	{
		throw new GameEvenException();
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
    
void PlayerTiger::setPlayerGoat(PlayerGoat *playerGoat)
{
	opponent = playerGoat;
}

PlayerGoat* PlayerTiger::getPlayerGoat()
{
	return opponent;
}
