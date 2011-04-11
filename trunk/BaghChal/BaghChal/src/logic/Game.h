/**
* Game Class
* @file Game.h
* @brief Headerfile for Game Class
* @see Game
* @author Julian Bayer
*/
#ifndef GAME_H
#define GAME_H
#include "Test.h" //This is for Test purposes only and must be removed when compiling the whole Game!

/**
* @class Game
* @brief Central class for game logic
* 
* The Game Class oversees all members of the game logic
*/
class Game
{
  public:
    Game() : grid(), tiger(), goat() {};
    ~Game () {};
    Grid& getGrid();
    PlayerTiger& getTiger();
    PlayerGoat& getGoat();
   
  private:
    Grid grid;		    	/**< Playing field */
    PlayerTiger tiger;		/**< Player, who controls the tigers */
    PlayerGoat goat;		/**< Player, who controls the goats */
};

#endif