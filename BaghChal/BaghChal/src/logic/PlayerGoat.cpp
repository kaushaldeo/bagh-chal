/**
 * @file PlayerGoat.cpp
 * @brief Implementation of PlayerGoat Class
 * @author Steffen Dittmar
 */

#include "PlayerGoat.h"
#include "Game.h"

PlayerGoat::PlayerGoat()
{
    goats = new Goat* [20];

    for(int i = 0; i < 20; i++)
    {
        goats[i] = new Goat();
    }

    nextGoat = 0;
}

PlayerGoat::PlayerGoat(PlayerTiger *playerTiger)
{
	opponent = playerTiger;

    goats = new Goat* [20];

    for(int i = 0; i < 20; i++)
    {
        goats[i] = new Goat();
    }

    nextGoat = 0;
}

PlayerGoat::~PlayerGoat()
{
    for(int i = 0; i < 20; i++)
    {
        delete goats[i];
    }

    delete[]  goats;
}

void PlayerGoat::setCell(Cell *cell)
{
    goats[nextGoat]->setCell(cell);
	cell->setGoat(goats[nextGoat]);
	cell->setStatus(goat);

    nextGoat++;
}

bool PlayerGoat::canMove()
{    
	if(nextGoat < 20)
	{
		return true;
	}

	for(int i = 0; i < 20; i++)
	{
		if(goats[i]->canMove())
		{
			return true;
		}
	}

	return false;
}

bool PlayerGoat::canMoveThere(Cell *src, Cell *dst)
{
	Goat *thisGoat;
	
	if(src == NULL)
	{
		if(dst->getStatus() != empty || nextGoat >= 20)
			return false;

		return true;
	}
	else
	{
		if(nextGoat < 20)
			return false;
	}

	try
	{
		thisGoat = src->getGoat();
	}
	catch(exception e)
	{
		return false;
	}

	return  thisGoat->canMoveThere(dst);
}

void PlayerGoat::move(Cell *src, Cell *dst)
{
	/*
	 * Warning, move doesn't do any reliable exception handling anymore,
	 * never call without calling canMoveThere first.
	 */

	if(src == NULL)
	{
		setCell(dst);
        }
        else
        {
            Goat * thisGoat;

            try
            {
                    thisGoat = src->getGoat();
            }
            catch(exception e)
            {
                    throw new CanNotMoveException();
            }

            thisGoat->move(dst);
        }

        Game::getInstance()->setTurn(tiger);
        Game::getInstance()->setChanged(true);

        if(!opponent->canMove())
        {
                Game::getInstance()->setTurn(empty);
                Game::getInstance()->setChanged(false);
                throw new GoatWonException();
        }
}

void PlayerGoat::setGoats(Goat** goats)
{
	this->goats = goats;
}

Goat** PlayerGoat::getGoats()
{
	return goats;
}

void PlayerGoat::setNextGoat(int number)
{
	nextGoat = number;
}

int PlayerGoat::getNextGoat()
{
	return nextGoat;
}

void PlayerGoat::setPlayerTiger(PlayerTiger *playerTiger)
{
	opponent = playerTiger;
}

PlayerTiger* PlayerGoat::getPlayerTiger()
{
	return opponent;
}


        


