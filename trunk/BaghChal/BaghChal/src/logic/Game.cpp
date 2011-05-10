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
Game::Game () : grid(), goatP(), changed(true), turn(goat)
{
  Cell* tigerCells[4] = {grid.getCell(0,0), grid.getCell(0,4), grid.getCell(4,4), grid.getCell(4,0)};
  tigerP (tigerCells);
}

void Game::setChanged (bool newChanged)
{
  changed = newChanged;
}

bool Game::getChanged ()
{
  return changed;
}
