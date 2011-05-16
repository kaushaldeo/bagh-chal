/**
* FileIO
* @file FileIO.cpp
* @brief Implementation file for File I/O
* @see FileIO
* @author Julian Bayer
*/
#include "FileIO.h"

using namespace std;

/**
 * @fn saveGame()
 * @brief Saves the game to a textfile.
 * @param game - Reference on a game object
 * 
 * Saves the Data from game into a textfile.
 */
void FileIO::saveGame ()
{
    Game* game = Game::getInstance();
  if (!game->getChanged() || game->getTurn() == empty) //If the game has just been saved/loaded or has already ended there's really no point saving it.
    return;
  
  fileStream << convertToInt(game->getTurn()) << " ";
  for (int i=0; i < 5; i++)
    for (int j=0; j < 5; j++)
    {
      Cell* cell = game->getGrid().getCell(i,j);
      fileStream << convertToInt(cell->getStatus()) << " ";
    }
  
  fileStream << game->getTiger().getScore();
  Tiger** tigers = game->getTiger().getTigers();
  for (int i=0;i<4;i++)
  {
    pair<int,int> pos = tigers[i]->getCell()->getPosition();
    fileStream << pos.first << " ";
    fileStream << pos.second << " ";
  }
  fileStream << game->getGoat().getNextGoat();
  Goat** goats = game->getGoat().getGoats();
  for (int i=0;i<20;i++)
  {
    pair<int,int> pos = goats[i]->getCell()->getPosition();
    fileStream << pos.first << " ";
    fileStream << pos.second << " ";
  }
  
  
  game->setChanged(false);
}


/**
 * @fn loadGame()
 * @brief Loads the game to a textfile.
 * @param game - Reference on a game object
 * 
 * Loads data from a textfile and loads it into a game class.
 */
void FileIO::loadGame ()
{
  
  int tmp;
    Game* game = Game::getInstance();
  
  fileStream >> tmp;
  game->setTurn(convertFromInt(tmp));
  for (int i=0; i < 5; i++)
    for (int j=0; j < 5; j++)
    {
      fileStream >> tmp;
      game->getGrid().getCell(i,j)->setStatus(convertFromInt(tmp));
    }
  
  fileStream >> tmp;
  game->getTiger().setScore(tmp);
  Tiger** tigers = game->getTiger().getTigers();
  for (int i=0;i<4;i++)
  {
    int x, y;
    fileStream >> x;
    fileStream >> y;
    tigers[i]->setCell(game->getGrid().getCell(x,y));
  }
  fileStream >> tmp;
  game->getGoat().setNextGoat(tmp);
  Goat** goats = game->getGoat().getGoats();
  for (int i=0;i<20;i++)
  {
    int x, y;
    fileStream >> x;
    fileStream >> y;
    goats[i]->setCell(game->getGrid().getCell(x,y));
  }
  
    game->setChanged(false);
  }
  
  CellStatus FileIO::convertFromInt (int state)
  {
    switch (state)
    {
      case 0: return empty;
      case 1: return tiger;
      case 2: return goat;
      default: throw new InvalidStateException();
    }
  }
  
  int FileIO::convertToInt (CellStatus state)
  {
    switch (state)
    {
      case empty: return 0;
      case tiger: return 1;
      case goat: return 2;
    }
    throw new exception();
  }