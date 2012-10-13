/**
* Game Class
* @file Game.h
* @brief Headerfile for Game Class
* @see Game
* @author Julian Bayer
*/
#ifndef GAME_H
#define GAME_H
#include "Grid.h"
#include "PlayerTiger.h"
#include "PlayerGoat.h"
#include "Enums.h"
#include <iostream>
#include <utility>

/**
* @class Game
* @brief Singleton class for the game
*
* The Game class oversees all members of the game logic.
*/
class Game
{
public:
    /**
     * @fn ~Game()
     * @brief Destructor
     * @see BaghChal::openNewGame
     *
     * A public destructor of game. This is used to create a new game.
     */
    ~Game()
    {
        game = 0;
    };

    /**
     * @fn &getGrid()
     * @brief Returns reference on grid object
     * @returns Grid&
     */
    Grid &getGrid();

    /**
     * @fn &getTiger()
     * @brief Returns reference on PlayerTiger object
     * @returns PlayerTiger&
     */
    PlayerTiger &getTiger();

    /**
     * @fn &getGoat()
     * @brief Returns reference on PlayerGoat object
     * @returns PlayerGoat&
     */
    PlayerGoat &getGoat();

    /**
     * @fn setChanged(bool)
     * @brief Set changed flag
     * @param newChanged - bool
     */
    void setChanged(bool);

    /**
     * @fn getChanged()
     * @brief Return changed flag
     * @returns bool
     */
    bool getChanged();

    /**
     * @fn getTurn()
     * @brief Returns which player's turn it is
     * @returns CellStatus
     */
    CellStatus getTurn();

    /**
     * @fn setTurn(CellStatus)
     * @brief Sets which player's turn it is
     * @param newturn - CellStatus
     */
    void setTurn(CellStatus);

    /**
     * @fn *getInstance()
     * @brief Static function returning game singleton object
     * @returns Game*
     *
     * Returns the game singleton object. If there is none, the method creates it.
     */
    static Game *getInstance();

    /**
     * @fn startNewGame()
     * @brief Static function to start a new game
     *
     * Deletes old game-Singleton and creates a new one.
     */
    static void startNewGame();

    /**
     * @fn *getLastEatenGoatCell()
     * @brief Returns pointer on cell, on which the last eaten goat was
     * @returns Cell*
     */
    Cell *getLastEatenGoatCell();

    /**
     * @fn setLastEatenGoatCell(Cell *cell)
     * @brief Sets pointer on cell, on which the last eaten goat was
     * @param cell - Cell*
     */
    void setLastEatenGoatCell(Cell *cell);

private:
    /**
     * @fn Game()
     * @brief Default-constructor for class Game
     *
     * Constructs a PlayerTiger, PlayerGoat, as well as the grid. This is private because the class is a singleton.
     */
    Game();
    static Game *game;          /**< Static pointer to a game instance */
    Grid grid;		    	/**< Playing field */
    PlayerTiger tigerP;		/**< Player, who controls the tigers */
    PlayerGoat goatP;		/**< Player, who controls the goats */
    bool changed;               /**< Has the game changed since the last save/load */
    CellStatus turn;            /**< Whos turn is it? 0 - no one, 1 tiger, 2 goat */
    Cell *lastEatenGoatCell;    /**< The cell containing the goat that was recently eaten */
};

#endif
