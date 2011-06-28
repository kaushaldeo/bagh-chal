/**
 * @file Game.cpp
 * @brief Implementation File for Game Class
 * @see Game.h
 * @author Julian Bayer
 */
#include "Game.h"

Game::Game() : grid(), goatP(), changed(false), turn(goat), lastEatenGoatCell(NULL)
{
    Cell *tigerCells[] = {grid.getCell(0, 0), grid.getCell(0, 4), grid.getCell(4, 4), grid.getCell(4, 0)};
    tigerP = PlayerTiger(tigerCells, &goatP);
    goatP.setPlayerTiger(&tigerP);
}

Game *Game::game = 0;

Game *Game::getInstance()
{
    if (!game)
    {
        game = new Game();
    }

    return game;
}

void Game::setChanged(bool newChanged)
{
    changed = newChanged;
}

bool Game::getChanged()
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

Grid &Game::getGrid()
{
    return grid;
}

PlayerTiger &Game::getTiger()
{
    return tigerP;
}

PlayerGoat &Game::getGoat()
{
    return goatP;
}

void Game::startNewGame()
{
    delete game;
    game = new Game();
}

Cell *Game::getLastEatenGoatCell()
{
    return lastEatenGoatCell;
}

void Game::setLastEatenGoatCell(Cell *cell)
{
    this->lastEatenGoatCell = cell;
}
