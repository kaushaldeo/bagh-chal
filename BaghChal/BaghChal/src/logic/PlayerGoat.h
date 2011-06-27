/** @file PlayerGoat.h
 *  @brief Headerfile for PlayerGoat class
 *  @author Steffen Dittmar
 */
 
#ifndef PLAYERGOAT_H
#define PLAYERGOAT_H

#include "Goat.h"
#include "Cell.h"
#include "PlayerTiger.h"
#include "Exceptions.h"

class PlayerTiger;

/**
 * @brief Class representing player controlling the goats
 */
class PlayerGoat
{
public:
    /**
     * @brief Default constructor for PlayerGoat
     *
     * Creates 20 instances of Goat and stores them in an array.
     */
    PlayerGoat();

    /**
     * @brief Overloaded constructor for PlayerGoat
     * @param playerTiger - A pointer to the opponent Player
     *
     * Creates 20 instances of Goat and stores them in an array and
     * registers playerTiger as the opponent.
     */
    PlayerGoat(PlayerTiger *playerTiger);

    /**
     * @brief Default destructor for PlayerGoat
     *
     * Deletes all instances of Goat and the array containing them.
     */
    ~PlayerGoat();

    /**
     * @brief Set the next goat that has not been placed yet on cell
     * @param cell - Cell to set the Goat to
     */
    void setCell(Cell *cell);

    /**
     * @brief Checks if any goat can make any valid moves
     * @return True if any goat can make any valid moves, else false
     */
    bool canMove();

    /**
     * @brief Checks if any goat can be moved from src to dst
     * @param src - The Cell the Goat should reside on
     * @param dst - The Cell to be checked if the goat residing on src could be moved to
     * @return True if a valid move is possble, else false
     *
     * If src is NULL, canMoveThere() checks if an unplaced goat could be placed on dst.
     */
    bool canMoveThere(Cell *src, Cell *dst);

    /**
     * @brief Moves a goat residing on src to dst if possible
     * @param src - The Cell which the goat should reside on
     * @param dst - The Cell which the goat should be moved to
     * @exception CanNotMoveException is thrown when a move from src to dst is not possible
     *
     * If src is NULL, an unplaced goat will be placed on dst if possible.
     */
    void move(Cell *src, Cell *dst);

    /**
     * @brief Setter for the array of goats controlled by PlayerGoat
     * @param goats - Array of pointers to instances of Goat
     */
    void setGoats(Goat **goats);

    /**
     * @brief Getter for the array of goats controlled by PlayerGoat
     * @return Array of pointers to instances of Goat
     */
    Goat **getGoats();

    /**
     * @brief Setter for the index in the array of the goats to be placed next
     * @param number - Index of the goat to be placed next
     */
    void setNextGoat(int number);

    /**
     * @brief Getter for the index in the array of the goats to be placed next
     * @return Index of the goat to be placed next
     */
    int getNextGoat();

    /**
     * @brief Setter for the pointer to the opponent player
     * @param playerTiger - Pointer to the opponent player
     */
    void setPlayerTiger(PlayerTiger *playerTiger);

    /**
     * @brief Getter for the pointer to the opponent player
     * @return playerTiger - Pointer to the opponent player
     */
    PlayerTiger *getPlayerTiger();

private:
    Goat **goats;			/**< Array containing pointers to all instances of Goat */
    int nextGoat; 			/**< Index of the next, not already placed goat */
    PlayerTiger *opponent;	        /**< Pointer to the opponent */
};

#endif
