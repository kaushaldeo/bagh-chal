/**
* FileIO
* @file FileIO.cpp
* @brief Implementation file for File I/O
* @see FileIO
* @author Julian Bayer
*/
#include "FileIO.h"
#include <fstream>

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
  if (!game->getChanged())
    return;
  ofstream fileStream (path.c_str());
  fileStream << convertToInt(game->getTurn()) << " ";
  Grid& grid = game->getGrid();
  fileStream << game->getTiger().getScore() << " ";
  fileStream << game->getGoat().getNextGoat() << endl;
  for (int i = 0; i < 5; i++)
    for (int j = 0; j < 5; j++)
    {
      Cell* cell = grid.getCell(i,j);
      if (cell->getStatus() != baghchal::empty)
        fileStream << i << " " << j << " " << convertToInt(cell->getStatus()) << endl;
    }
 
    
  fileStream << 1024;
  game->setChanged(false);
  fileStream.close();
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
  ifstream fileStream (path.c_str());
  int tmp;
  Game* game = Game::getInstance();
  game->startNewGame();
  fileStream >> tmp;
  game->setTurn(convertFromInt(tmp));
  fileStream >> tmp;
  game->getTiger().setScore(tmp);
  fileStream >> tmp;
  game->getGoat().setNextGoat(tmp);
  

  Tiger** tigers = game->getTiger().getTigers();
  Goat** goats = game->getGoat().getGoats();
  int goatCounter = game->getTiger().getScore();
  int tigerCounter = 0;
  
  while(true)
  {
    if (fileStream.eof())
      throw InvalidInputFileException ();
    int x;
    int y;
    int istatus;
    fileStream >> x;
    if (x == 1024)
      break;
    if (fileStream.eof() || tigerCounter >= 4 || (game->getGoat().getNextGoat() != 0 && goatCounter >= game->getGoat().getNextGoat()))
      throw InvalidInputFileException ();
    fileStream >> y;
    if (fileStream.eof())
      throw InvalidInputFileException ();
    fileStream >> istatus;
    if (fileStream.eof())
      throw InvalidInputFileException ();
    baghchal::CellStatus status = convertFromInt(istatus);

    if (x >= 5 || y >= 5 || status == baghchal::empty)
      throw InvalidInputFileException ();
    Cell* cell = game->getGrid().getCell(x,y);
    cell->setStatus(convertFromInt(istatus));
    if (status==baghchal::tiger)
    {
      tigers[tigerCounter]->setCell(cell);
      tigerCounter++;
    }
    else if (status == baghchal::goat)
    {
      goats[goatCounter]->setCell(cell);
      goatCounter++;
    }
  }
  
  game->setChanged(false);
  fileStream.close();
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