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
* @brief Central class for game logic
* 
* The Game Class oversees all members of the game logic
*/
class Game
{
  public:
    ~Game () {game = 0;};
    Grid& getGrid();
    PlayerTiger& getTiger();
    PlayerGoat& getGoat();
    void setChanged(bool);
    bool getChanged();
    CellStatus getTurn ();
    void setTurn (CellStatus);
    static Game* getInstance();
    static void startNewGame();
    
	Cell* getLastEatenGoatCell();
	void setLastEatenGoatCell(Cell* cell);

  private:
    Game();
    static Game* game;
    Grid grid;		    	/**< Playing field */
    PlayerTiger tigerP;		/**< Player, who controls the tigers */
    PlayerGoat goatP;		/**< Player, who controls the goats */
    bool changed;           /**< Has the game changed since the last save/load */
    CellStatus turn;        /**< Whos turn is it? 0 - no one, 1 tiger, 2 goat */
	Cell* lastEatenGoatCell; /**< The cell containing the goat that was recently eaten */
};

#endif
