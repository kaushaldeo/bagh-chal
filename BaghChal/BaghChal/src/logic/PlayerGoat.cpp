/**
 * @file PlayerGoat.cpp
 * @brief Implementation of PlayerGoat Class
 * @author Steffen Dittmar
 */

#include "PlayerGoat.h"
#include "Game.h"

/**
 * @brief Default constructor for PlayerGoat
 *
 * Creates 20 instances of Goat and stores them in an array.
 */
PlayerGoat::PlayerGoat()
{
    goats = new Goat* [20];

    for(int i = 0; i < 20; i++)
    {
        goats[i] = new Goat();
    }

    nextGoat = 0;
}

/**
 * @brief Overloaded constructor for PlayerGoat
 * @param playerTiger A pointer to the opponent Player
 *
 * Creates 20 instances of Goat and stores them in an array and
 * registers playerTiger as this PlayerGoats opponent.
 */
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

/**
 * @brief Default destructor for PlayerGoat
 *
 * Deletes all instances of Goat and the Array containing them.
 */
PlayerGoat::~PlayerGoat()
{
    for(int i = 0; i < 20; i++)
    {
        delete goats[i];
    }

    delete[]  goats;
}

/**
 * @brief Set the next Goat that has not been placed yet on cell
 * @param cell Cell to set the Goat to
 */
void PlayerGoat::setCell(Cell *cell)
{
    goats[nextGoat]->setCell(cell);
	cell->setGoat(goats[nextGoat]);
	cell->setStatus(goat);

    nextGoat++;
}

/**
 * @brief Checks if any Goat can make any valid moves
 * @return True if any Goat can make any valid moves, else false
 */
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

/**
 * @brief Checks if any Goat can be moved from src to dst
 * @param src The Cell the Goat should reside on
 * @param dst The Cell to be checked if the Goat residing on src could be moved to
 * @return True if a valid move is possble, else false
 *
 * If src is NULL, canMoveThere checks if an unplaced Goat could be placed on dst.
 */
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

/**
 * @brief Moves Goat residing on src to dst if possible
 * @param src The Cell the Goat should reside on
 * @param dst The Cell the Goat should be moved to
 * @exception CanNotMoveException Is thrown when a move from src to dst is not possible
 *
 * If src is NULL, an unplaced Goat will be placed on dst if possible.
 */
void PlayerGoat::move(Cell *src, Cell *dst)
{
    if( !canMoveThere(src, dst) )
    {
        throw new CanNotMoveException();
    }
    
	if(src == NULL)
	{
		if(dst->getStatus() != empty)
		{
			throw new CanNotMoveException();
		}

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

/**
 * @brief Setter for the array of Goats controlled by PlayerGoat
 * @param goats Array of pointers to instances of Goat
 */
void PlayerGoat::setGoats(Goat** goats)
{
	this->goats = goats;
}

/**
 * @brief Getter for the array of Goats controlled by PlayerGoat
 * @return Array of pointers to instances of Goat
 */
Goat** PlayerGoat::getGoats()
{
	return goats;
}

/**
 * @brief Setter for the index in the array of the Goat to be placed next
 * @param number Index of the Goat to be placed next
 */
void PlayerGoat::setNextGoat(int number)
{
	nextGoat = number;
}

/**
 * @brief Getter for the index in the array of the Goat to be placed next
 * @return Index of the Goat to be placed next
 */
int PlayerGoat::getNextGoat()
{
	return nextGoat;
}

/**
 * @brief Setter for the pointer to the opponent player
 * @param playerTiger Pointer to the opponent player
 */
void PlayerGoat::setPlayerTiger(PlayerTiger *playerTiger)
{
	opponent = playerTiger;
}

/**
 * @brief Getter for the pointer to the opponent player
 * @return playerTiger Pointer to the opponent player
 */
PlayerTiger* PlayerGoat::getPlayerTiger()
{
	return opponent;
}


        


