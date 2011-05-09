/**
 * @file Game.cpp
 * @brief Implementation File for class Game
 * @see Game.h
 */

#include "Game.h"

/**
 * @fn Game()
 * @brief Default-constructor for class Game
 * 
 * Constructs a PlayerTiger, PlayerGoat, as well as the grid
 */
Game::Game () : grid(), goat(), turn(2), changed(true)
{
  Cell* tigerCells[4] = {grid.getCell(0,0), grid.getCell(0,4), grid.getCell(4,4), grid.getCell(4,0)};
  tiger (tigerCells);
}

void setChanged (bool newChanged)
{
  changed = newChanged;
}

bool getChanged ()
{
  return changed;
}
