/**
 * @file PlayerGoat.cpp
 * @brief Implementation of PlayerGoat Class
 * @author Steffen Dittmar
 */

#include "Game.h"
#include "PlayerGoat.h"

PlayerGoat::PlayerGoat()
{
    goats = new Goat* [20];

    for (int i = 0; i < 20; i++)
    {
        goats[i] = new Goat();
    }

    nextGoat = 0;
}

PlayerGoat::PlayerGoat(PlayerTiger *playerTiger)
{
    opponent = playerTiger;

    goats = new Goat* [20];

    for (int i = 0; i < 20; i++)
    {
        goats[i] = new Goat();
    }

    nextGoat = 0;
}

PlayerGoat::~PlayerGoat()
{
    for (int i = 0; i < 20; i++)
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
    //Not all goats have been set
    if (nextGoat < 20)
    {
        return true;
    }

    //For every goat
    for (int i = 0; i < 20; i++)
    {
        if (goats[i]->canMove())
        {
            //At least one goat can move
            return true;
        }
    }

    //No goat can make any valid moves anymore
    return false;
}

bool PlayerGoat::canMoveThere(Cell *src, Cell *dst)
{
    Goat *thisGoat;

    if (src == NULL)
    {
        //Set an unset Goat
        if (dst->getStatus() != empty || nextGoat >= 20)
        {
            //The cell the goat is tried to be set on is not empty
            //or all goats have already been set
            return false;
        }

        //Goat can be set on dst
        return true;
    }
    else
    {
        //Move an already set goat
        if (nextGoat < 20)
        {
            //Not all goats have been set yet
            return false;
        }
    }

    try
    {
        thisGoat = src->getGoat();
    }
    catch (exception e)
    {
        //No goat resides on cell src
        return false;
    }

    return  thisGoat->canMoveThere(dst);
}

void PlayerGoat::move(Cell *src, Cell *dst)
{
    if (!canMoveThere(src, dst))
    {
        throw new CanNotMoveException();
    }

    if (src == NULL)
    {
        //Set an unset Goat
        if (dst->getStatus() != empty)
        {
            //The cell the goat is tried to be set on is not empty
            throw new CanNotMoveException();
        }

        setCell(dst);
    }
    else
    {
        Goat *thisGoat;

        try
        {
            thisGoat = src->getGoat();
        }
        catch (exception e)
        {
            //No goat resides on cell src
            throw new CanNotMoveException();
        }

        thisGoat->move(dst);
    }

    //Move successfull, it's PlayerTigers turn now
    Game::getInstance()->setTurn(tiger);
    Game::getInstance()->setChanged(true);

    if (!opponent->canMove())
    {
        //PlayerTiger can't make any valid moves anymore, PlayerGoat won
        Game::getInstance()->setTurn(empty);
        Game::getInstance()->setChanged(false);
        throw new GoatWonException();
    }
}

void PlayerGoat::setGoats(Goat **goats)
{
    this->goats = goats;
}

Goat **PlayerGoat::getGoats()
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

PlayerTiger *PlayerGoat::getPlayerTiger()
{
    return opponent;
}
