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

	//Deep-copy all Tigers
    for (int i = 0; i < 4; ++i)
    {
		//Set status of the cell this tiger resides on to empty
		//to avoid setCell(), which is called by the constructor
		//of Tiger, to throw an exception
        srcTigers[i]->getCell()->setStatus(empty);
		//Will set the status of the cell to tiger again
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
        {
            //At least one tiger can move
            return true;
        }
    }

    //No tiger can move
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
		//No tiger resides on cell src
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
		//No tiger resides on cell src
        throw new CanNotMoveException();
    }

	//If any goat could be eaten, it has to be eaten
    bool mustEat = couldEat();

    if (thisTiger->move(dst, mustEat))
    {
		//A goat has been eaten
        score++;

        if (score > 0 && score < 5)
        {
			//Tiger has not yet won, it's PlayerGoats turn now
            Game::getInstance()->setTurn(goat);
            Game::getInstance()->setChanged(true);
            throw new TigerEatGoatException();
        }
        else if (score == 5)
        {
			//Tiger has won
            Game::getInstance()->setTurn(empty);
            Game::getInstance()->setChanged(false);
            throw new TigerWonException();
        }
    }

	//Move successfull, no goat has been eaten, it's PlayerGoats turn now
    Game::getInstance()->setTurn(goat);
    Game::getInstance()->setChanged(true);

    if (!opponent->canMove())
    {
		//PlayerGoat can't make any valid moves anymore, the game is even
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
