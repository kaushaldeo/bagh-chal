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

/**
 * @fn getTurn
 * @brief returns which player's turn it is
 * @returns CellStatus
 * @see CellStatus
 */
CellStatus Game::getTurn()
{
  return turn;
}

/**
 * @fn setTurn
 * @brief sets which player's turn it is
 * @param newturn - CellStatus
 * @see CellStatus
 */
void Game::setTurn(CellStatus newturn)
{
  turn = newturn;
}

/**
 * @fn getGrid
 * @brief returns reference on grid object
 * @returns Grid&
 */
Grid& Game::getGrid()
{
  return grid;
}

/**
 * @fn getTiger
 * @brief returns reference on PlayerTiger object
 * @returns PlayerTiger&
 */
PlayerTiger& Game::getTiger()
{
  return tigerP;
}

/**
 * @fn getGoat
 * @brief returns reference on PlayerGoat object
 * @returns PlayerGoat&
 */
PlayerGoat& Game::getGoat()
{
  return goatP;
}

/**
 * @fn startNewGame
 * @brief static function to start a new game
 * 
 * Deletes old game-Singleton and creates a new one
 */
void Game::startNewGame()
{
  delete game;
  game = new Game();
}
  

/**
 * @fn getLastEatenGoatCell()
 * @brief returns pointer on cell, on which the last eaten goat was sitting
 * @returns Cell*
 */
Cell* Game::getLastEatenGoatCell()
{
	return lastEatenGoatCell;
}



/**
 * @fn getLastEatenGoatCell()
 * @brief sets pointer on cell, on which the last eaten goat was sitting
 * @param cell - Cell*
 */
void Game::setLastEatenGoatCell(Cell* cell)
{
	this->lastEatenGoatCell = cell;
}

