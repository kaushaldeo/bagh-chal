/** @file PlayerTiger.h
 *  @brief Headerfile for PlayerTiger class
 *  @author Steffen Dittmar
 */
#ifndef PLAYERTIGER_H
#define PLAYERTIGER_H

#include "Tiger.h"
#include "Cell.h"
#include "PlayerGoat.h"
#include "Exceptions.h"

class PlayerGoat;

/**
* @class PlayerTiger
* @brief Class of the player with the tiger
*
* This class is representing the player who controls the tiger.
*/
class PlayerTiger
{
public:
    /**
     * @fn PlayerTiger()
     * @brief Default constructor for PlayerTiger
     *
     * Does nothing at all.
     */
    PlayerTiger();

    /**
     * @fn PlayerTiger(Cell *tigerCells[])
     * @brief Overloaded constructor for PlayerTiger
     * @param tigerCells - Array of 4 pointers to the cells the tigers should be placed on
     *
     * Creates 4 new instances of Tiger and places them on the cells passed as parameter,
     * which should be the corners of the grid.
     */
    PlayerTiger(Cell *tigerCells[]);
    

    /**
     * @fn PlayerTiger(Cell **tigerCells, PlayerGoat *playerGoat)
     * @brief Overloaded constructor for PlayerTiger
     * @param tigerCells - Array of 4 pointers to the cells the tigers should be placed on
     * @param playerGoat - A pointer to the opponent Player
     *
     * Creates 4 new instances of Tiger and places them on the cells passed as parameter,
     * which should be the corners of the grid and registers playerGoat as the opponent.
     */
    PlayerTiger(Cell **tigerCells, PlayerGoat *playerGoat);

    /**
     * @fn ~PlayerTiger()
     * @brief Default destructor for PlayerTiger
     *
     * Deletes all instances of Tiger and the array containing them.
     */
    ~PlayerTiger();

    /**
     * @fn &operator= (const PlayerTiger &src)
     * @brief Overloaded operator = for PlayerTiger
     *
     * Deep copies the array of tigers and copies score and opponent.
     */
    PlayerTiger &operator= (const PlayerTiger &src);
    
    /**
     * @fn canMove()
     * @brief Checks if any tiger can make any valid moves
     * @return True if any tiger can make any valid moves, else false
     */
    bool canMove();

    /**
     * @fn canMoveThere(Cell *src, Cell *dst)
     * @brief Checks if any tiger can be moved from src to dst
     * @param src - The Cell which the tiger should reside on
     * @param dst - The Cell which to be checked if the tiger residing on src could be moved to
     * @return True if a valid move is possible, else false
     */
    bool canMoveThere(Cell *src, Cell *dst);

    /**
     * @fn move(Cell *src, Cell *dst)
     * @brief Moves tiger residing on src to dst if possible
     * @param src - The Cell the Tiger should reside on
     * @param dst - The Cell the Tiger should be moved to
     * @exception CanNotMoveException is thrown when a move from src to dst is not possible
     */
    void move(Cell *src, Cell *dst);

    /**
     * @fn setScore(int score)
     * @brief Setter for the number of goats eaten by all tigers
     * @param score - Number of goats eaten by all tigers
     */
    void setScore(int score);
    
    /**
     * @fn getScore()
     * @brief Getter for the number of goats eaten by all tigers
     * @returns Number of goats eaten by all tigers
     */
    int getScore();
    
    /**
     * @fn setTigers(Tiger **tigers)
     * @brief Setter for the array of tigers controlled by PlayerTiger
     * @param tigers - Array of pointers to instances of Tiger
     */
    void setTigers(Tiger **tigers);

    /**
     * @fn **getTigers()
     * @brief Getter for the array of tigers controlled by PlayerTiger
     * @return Array of pointers to instances of Tiger
     */
    Tiger **getTigers();

    /**
     * @fn setPlayerGoat(PlayerGoat *playerGoat)
     * @brief Setter for the pointer to the opponent player
     * @param playerGoat - Pointer to the opponent player
     */
    void setPlayerGoat(PlayerGoat *playerGoat);

    /**
     * @fn *getPlayerGoat()
     * @brief Getter for the pointer to the opponent player
     * @return Pointer to the opponent player
     */
    PlayerGoat *getPlayerGoat();
    
    /**
     * @brief Checks if any tiger could eat a goat
     * @return True if any tiger could eat a goat, else false
     */
    bool couldEat();

private:
    Tiger **tigers;	                /**< Array containing pointers to all instances of Tiger */	
    int score;  	                /**< Number of goats eaten by all tigers */
    PlayerGoat *opponent;	        /**< Pointer to the opponent */
};

#endif
