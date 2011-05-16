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
  Cell* tigerCells[] = {grid.getCell(0,0), grid.getCell(0,4), grid.getCell(4,4), grid.getCell(4,0)};
  tigerP = PlayerTiger (tigerCells, &goatP);
  goatP.setPlayerTiger (&tigerP);
}

void Game::setChanged (bool newChanged)
{
  changed = newChanged;
}

bool Game::getChanged ()
{
  return changed;
}

CellStatus Game::getTurn()
{
  return turn;
}

void Game::setTurn(CellStatus newturn)
{
  turn = newturn;
}

Grid& Game::getGrid()
{
  return grid;
}

PlayerTiger& Game::getTiger()
{
  return tigerP;
}

PlayerGoat& Game::getGoat()
{
  return goatP;
}