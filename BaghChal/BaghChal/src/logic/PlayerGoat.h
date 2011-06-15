#ifndef PLAYERGOAT_H
#define PLAYERGOAT_H

#include "Goat.h"
#include "Cell.h"
#include "PlayerTiger.h"
#include "Exceptions.h"

/** @file PlayerGoat.h
 *  @brief Headerfile for PlayerGoat class
 *  @author Steffen Dittmar	
 */

class PlayerTiger;

/**
 * @brief Class representing Player controlling the Goats
 */
class PlayerGoat
{
public:
    PlayerGoat();
	PlayerGoat(PlayerTiger *playerTiger);
    ~PlayerGoat();
    void setCell(Cell *cell);
	bool canMove();
	bool canMoveThere(Cell *src, Cell *dst);
    void move(Cell*src, Cell *dst);
	void setGoats(Goat** goats);
	Goat** getGoats();
	void setNextGoat(int number);
	int getNextGoat();
	void setPlayerTiger(PlayerTiger *playerTiger);
	PlayerTiger* getPlayerTiger();

private:
    Goat **goats;			/**< Array containing pointers to all instances of Goat */
    int nextGoat; 			/**< Index of the next, not already placed goat */
	PlayerTiger *opponent;	/**< Pointer to the opponent */
};

#endif
