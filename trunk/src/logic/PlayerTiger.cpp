/**
 * @file PlayerTiger.cpp
 * @brief Implementation of PlayerTiger Class
 * @author Steffen Dittmar
 */

#include "Game.h"
#include "PlayerTiger.h"

PlayerTiger::PlayerTiger()
{
}

PlayerTiger::PlayerTiger(Cell *tigerCells[])
{
    tigers = new Tiger* [4];

    for (int i = 0; i < 4; i++)
    {
        tigers[i] = new Tiger(tigerCells[i]);
    }

    score = 0;
}

PlayerTiger::PlayerTiger(Cell **tigerCells, PlayerGoat *playerGoat)
{
    opponent = playerGoat;

    tigers = new Tiger* [4];

    for (int i = 0; i < 4; i++)
    {
        tigers[i] = new Tiger(tigerCells[i]);
    }

    score = 0;
}

PlayerTiger::~PlayerTiger()
{
    for (int i = 0; i < 4; i++)
    {
        delete tigers[i];
    }

    delete[] tigers;
}

PlayerTiger &PlayerTiger::operator=(const PlayerTiger &src)
{
    this->tigers = new Tiger* [4];

    Tiger **srcTigers = src.tigers;

    for (int i = 0; i < 4; ++i)
    {

        srcTigers[i]->getCell()->setStatus(empty);
        tigers[i] = new Tiger(srcTigers[i]->getCell());
    }

    opponent = src.opponent;

    score = src.score;

    return *this;
}

bool PlayerTiger::canMove()
{
    if (Game::getInstance()->getTurn() != tiger)
    {
        return false;
    }

    for (int i = 0; i < 4; i++)
    {
        if (tigers[i]->canMove())
            //at least one tiger can move
        {
            return true;
        }
    }

    //no tiger can move
    return false;
}

bool PlayerTiger::canMoveThere(Cell *src, Cell *dst)
{
    Tiger *thisTiger;

    try
    {
        thisTiger = src->getTiger();
    }
    catch (exception e)
    {
        return false;
    }

    return thisTiger->canMoveThere(dst);
}

void PlayerTiger::move(Cell *src, Cell *dst)
{
    if (!canMoveThere(src, dst))
    {
        throw new CanNotMoveException();
    }

    Tiger *thisTiger;

    try
    {
        thisTiger = src->getTiger();
    }
    catch (exception e)
    {
        throw new CanNotMoveException();
    }

    bool mustEat = couldEat();

    if (thisTiger->move(dst, mustEat))
    {
        score++;

        if (score > 0 && score < 5)
        {
            Game::getInstance()->setTurn(goat);
            Game::getInstance()->setChanged(true);
            throw new TigerEatGoatException();
        }
        else if (score == 5)
        {
            Game::getInstance()->setTurn(empty);
            Game::getInstance()->setChanged(false);
            throw new TigerWonException();
        }
    }

    Game::getInstance()->setTurn(goat);
    Game::getInstance()->setChanged(true);

    if (!opponent->canMove())
    {
        Game::getInstance()->setTurn(empty);
        Game::getInstance()->setChanged(false);
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

Tiger **PlayerTiger::getTigers()
{
    return tigers;
}

void PlayerTiger::setPlayerGoat(PlayerGoat *playerGoat)
{
    opponent = playerGoat;
}

PlayerGoat *PlayerTiger::getPlayerGoat()
{
    return opponent;
}

bool PlayerTiger::couldEat()
{
    for (int i = 0; i < 4; ++i)
    {
        if (tigers[i]->couldEat())
        {
            return true;
        }
    }

    return false;
}