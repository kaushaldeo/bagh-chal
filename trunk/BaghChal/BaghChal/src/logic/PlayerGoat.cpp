/**
 * @file PlayerGoat.cpp
 * @brief Implementation of PlayerGoat Class
 * @author Steffen Dittmar
 */

#include "PlayerGoat.h"

PlayerGoat::PlayerGoat()
{
    goats = new Goat *goats[20];

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

    nextGoat++;
}

void PlayerGoat::move(Cell *src, Cell *dst)
{
    int i = 0;

	try
	{
		Goat *thisGoat = src->getGoat();
	}
	catch(Exception e)
	{
		throw new CanNotMoveException();
	}

    thisGoat->move(dst);
}

void PlayerGoat::setGoats(int placeholder)
{

}

void PlayerGoat::getGoats()
{

}

void PlayerGoat::setNextGoat(int placeholder)
{

}

void PlayerGoat::getNextGoat();


        


