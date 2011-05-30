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


Game* Game::game = 0;

Game* Game::getInstance()
{
    if( !game )
    {
        game = new Game();
    }
    return game;
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


void Game::startNewGame()
{
  grid = Grid();
  Cell* tigerCells[] = {grid.getCell(0,0), grid.getCell(0,4), grid.getCell(4,4), grid.getCell(4,0)};
  goatP = PlayerGoat();
  tigerP = PlayerTiger(tigerCells, &goatP);
  goatP.setPlayerTiger (&tigerP);
  changed = true;
}
  

/**
 * @fn Game()
 * @brief Default-constructor for class Game
 * 
 * Constructs a PlayerTiger, PlayerGoat, as well as the grid
 */
std::pair<int, int> Game::getLastEatenGoatCell()
{
	return lastEatenGoat;
}


/**
 * @fn Game()
 * @brief Default-constructor for class Game
 * 
 * Constructs a PlayerTiger, PlayerGoat, as well as the grid
 */
void Game::setLastEatenGoatCell(std::pair<int, int> coordinates)
{
	lastEatenGoat = coordinates;
}

