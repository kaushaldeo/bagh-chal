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

void move(Cell *src, Cell *dst)
{
    int i = 0;
    while(src != goats[i]->getCell())
    {
        if(i >= 19)
            //no goat resides on src
            throw InvalidSourceException;
    
        i++;
    }

    goats[i]->move(dst);
}



        


