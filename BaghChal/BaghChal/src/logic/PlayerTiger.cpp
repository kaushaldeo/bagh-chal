/**
 * @file PlayerTiger.cpp
 * @brief Implementation of TigerPlayer Class
 * @author Steffen Dittmar
 */

#include "PlayerTiger.h"
#include "Game.h"

#include <iostream>

/**
 * @brief Default constructor for PlayerTiger
 *
 * Does nothing at all.
 */
PlayerTiger::PlayerTiger()
{
}

/**
 * @brief Overloaded constructor for PlayerTiger
 * @param tigerCells Array of 4 pointers to the cells the tigers should be placed on
 *
 * Creates 4 new instances of Tiger and places them on the Cells passed as parameter,
 * which should be the cornes of the Grid.
 */
PlayerTiger::PlayerTiger(Cell *tigerCells[])
{
    tigers = new Tiger* [4];

    for(int i = 0; i < 4; i++)
    {
        tigers[i] = new Tiger(tigerCells[i]);
    }

    score = 0;
}

/**
 * @brief Overloaded constructor for PlayerTiger
 * @param tigerCells Array of 4 pointers to the cells the tigers should be placed on
 * @param playerGoat A pointer to the opponent Player
 *
 * Creates 4 new instances of Tiger and places them on the Cells passed as parameter,
 * which should be the cornes of the Grid and registers playerTiger as this PlayerGoats opponent.
 */
PlayerTiger::PlayerTiger(Cell **tigerCells, PlayerGoat *playerGoat)
{
	opponent = playerGoat;

    tigers = new Tiger* [4];

    for(int i = 0; i < 4; i++)
    {
        tigers[i] = new Tiger(tigerCells[i]);
    }

    score = 0;
}

/**
 * @brief Default destructor for PlayerTiger
 *
 * Deletes all instances of Tiger and the array containing them.
 */
PlayerTiger::~PlayerTiger()
{
    for(int i = 0; i < 4; i++)
    {
        delete tigers[i];
    }

    delete[] tigers;
}

/**
 * @brief Overloaded operator = for PlayerTiger
 *
 * Deep copies the array of tigers and copies score and opponent.
 */
PlayerTiger& PlayerTiger::operator=(const PlayerTiger& src)
{
	this->tigers = new Tiger* [4];

	Tiger **srcTigers = src.tigers;

	for(int i = 0; i < 4; ++i)
	{

		srcTigers[i]->getCell()->setStatus(empty);
		tigers[i] = new Tiger(srcTigers[i]->getCell());
	}

	opponent = src.opponent;

        score = src.score;

	return *this;
}
/**
 * @brief Checks if any Tiger can make any valid moves
 * @return True if any Tiger can make any valid moves, else false
 */
bool PlayerTiger::canMove()
{
    if(Game::getInstance()->getTurn() != tiger)
    {
        return false;
    }
    
    for(int i = 0; i < 4; i++)
    {
        if(tigers[i]->canMove())
            //at least one tiger can move
            return true;
    }

    //no tiger can move
    return false;
}

/**
 * @brief Checks if any Tiger can be moved from src to dst
 * @param src The Cell the Tiger should reside on
 * @param dst The Cell to be checked if the Tiger residing on src could be moved to
 * @return True if a valid move is possble, else false
 */
bool PlayerTiger::canMoveThere(Cell *src, Cell *dst)
{
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

/**
 * @brief Moves Tiger residing on src to dst if possible
 * @param src The Cell the Tiger should reside on
 * @param dst The Cell the Tiger should be moved to
 * @exception CanNotMoveException Is thrown when a move from src to dst is not possible
 */
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

	bool mustEat = couldEat();

	if( thisTiger->move(dst, mustEat) )
	{
		score++;
	    if( score > 0 && score < 5 )
	    {
                Game::getInstance()->setTurn(goat);
                Game::getInstance()->setChanged(true);
	        throw new TigerEatGoatException();
	    }
	    else if( score == 5 )
	    {
                Game::getInstance()->setTurn(empty);
                Game::getInstance()->setChanged(false);
                throw new TigerWonException();
	    }
        }

        Game::getInstance()->setTurn(goat);
        Game::getInstance()->setChanged(true);

        if(!opponent->canMove())
        {
                Game::getInstance()->setTurn(empty);
                Game::getInstance()->setChanged(false);
                throw new GameEvenException();
        }
}

/**
 * @brief Getter for the number of goats eaten by all Tigers
 * @returns Number of goats eaten by all Tigers
 */
int PlayerTiger::getScore()
{
	return score;
}

/**
 * @brief Setter for the number of goats eaten by all Tigers
 * @param score Number of goats eaten by all Tigers
 */
void PlayerTiger::setScore(int score)
{
	this->score = score;
}

/**
 * @brief Setter for the array of Tigers controlled by PlayerTiger
 * @param tigers Array of pointers to instances of Tiger
 */
void PlayerTiger::setTigers(Tiger **tigers)
{
	this->tigers = tigers;
}

/**
 * @brief Getter for the array of Tigers controlled by PlayerTiger
 * @return Array of pointers to instances of Tiger
 */
Tiger** PlayerTiger::getTigers()
{
	return tigers;
}

/**
 * @brief Setter for the pointer to the opponent player
 * @param playerGoat Pointer to the opponent player
 */
void PlayerTiger::setPlayerGoat(PlayerGoat *playerGoat)
{
	opponent = playerGoat;
}
/**
 * @brief Getter for the pointer to the opponent player
 * @return Pointer to the opponent player
 */
PlayerGoat* PlayerTiger::getPlayerGoat()
{
	return opponent;
}

/**
 * @brief Checks if any tiger could eat a goat
 * @return True if any tiger could eat a goat, else false
 */
bool PlayerTiger::couldEat()
{
	for(int i = 0; i < 4; ++i)
	{
		if(tigers[i]->couldEat())
		{
			return true;
		}
	}
	return false;
}
