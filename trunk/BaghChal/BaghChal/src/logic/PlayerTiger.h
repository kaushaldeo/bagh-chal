#ifndef PLAYERTIGER_H
#define PLAYERTIGER_H

#include "Tiger.h"
#include "Cell.h"
#include "PlayerGoat.h"
#include "Exceptions.h"

/** @file PlayerTiger.h
 *  @brief Headerfile for PlayerTiger class
 *  @author Steffen Dittmar
 */

class PlayerGoat;

/**
 * @brief Class representing Player controlling the Tigers
 */
class PlayerTiger
{
public:
    PlayerTiger();
    PlayerTiger(Cell *tigerCells[]);
    PlayerTiger(Cell **tigerCells, PlayerGoat *playerGoat);
    ~PlayerTiger();
    PlayerTiger &operator= (const PlayerTiger &src);
    bool canMove();
    bool canMoveThere(Cell *src, Cell *dst);
    void move(Cell *src, Cell *dst);
    void setScore(int score);
    int getScore();
    void setTigers(Tiger **tigers);
    Tiger **getTigers();
    void setPlayerGoat(PlayerGoat *playerGoat);
    PlayerGoat *getPlayerGoat();
    bool couldEat();

private:
    Tiger **tigers;			/**< Array containing pointers to all instances of Tiger */
    int score;  			/**< Number of goats eaten by all tigers */
    PlayerGoat *opponent;	/**< Pointer to the opponent */
};

#endif
