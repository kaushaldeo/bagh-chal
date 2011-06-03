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
Game::Game () : grid(), goatP(), changed(false), turn(goat), lastEatenGoatCell(NULL)
{
  Cell* tigerCells[] = {grid.getCell(0,0), grid.getCell(0,4), grid.getCell(4,4), grid.getCell(4,0)};
  tigerP = PlayerTiger (tigerCells, &goatP);
  goatP.setPlayerTiger (&tigerP);
}


Game* Game::game = 0;

/**
 * @fn getInstance()
 * @brief static function returning game singleton object
 * @returns Game*
 * 
 * Returns the game singleton object. If there is none, creates it.
 */
Game* Game::getInstance()
{
    if( !game )
    {
        game = new Game();
    }
    return game;
}

/**
 * @fn setChanged
 * @brief set changed flag
 * @param newChanged - bool
 */
void Game::setChanged (bool newChanged)
{
  changed = newChanged;
}

/**
 * @fn getChanged
 * @brief return changed flag
 * @returns bool
 */
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
  delete game;
  game = new Game();
}
  

/**
 * @fn Game()
 * @brief Default-constructor for class Game
 * 
 * Constructs a PlayerTiger, PlayerGoat, as well as the grid
 */
Cell* Game::getLastEatenGoatCell()
{
	return lastEatenGoatCell;
}


/**
 * @fn Game()
 * @brief Default-constructor for class Game
 * 
 * Constructs a PlayerTiger, PlayerGoat, as well as the grid
 */
void Game::setLastEatenGoatCell(Cell* cell)
{
	this->lastEatenGoatCell = cell;
}

