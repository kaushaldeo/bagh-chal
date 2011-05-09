/**
* FileIO
* @file FileIO.cpp
* @brief Implementation file for File I/O
* @see FileIO
* @author Julian Bayer
*/

using namespace std;

/**
 * @fn saveGame()
 * @brief Saves the game to a textfile.
 * @param game - Reference on a game object
 * 
 * Saves the Data from game into a textfile.
 */
void FileIO::saveGame (Game& game)
{
  if (!game.getChanged() || game.getTurn() == 0) //If the game has just been saved/loaded or has already ended there's really no point saving it.
    return;
  
  fileStream << game.turn() << " ";
  for (int i=0; i < 5; i++)
    for (int j=0; j < 5; j++)
    {
      Cell* cell = game.getGrid().getCell(i,j);
      fileStream << cell->getStatus() << " ";
    }
  
  fileStream << game.getTiger().getScore();
  Tiger** tigers = game.getTiger().getTigers();
  for (int i=0;j<4;j++)
  {
    pair<int,int> pos = tigers[i]->getCell()->getPosition();
    fileStream << pos.first << " ";
    fileStream << pos.second << " ";
  }
  fileStream << game.getGoat().getNextGoat();
  Goat** goats = game.getGoat().getGoats();
  for (int i=0;i<20;i++)
  {
    pair<int,int> pos = goats[i]->getCell()->getPosition();
    fileStream << pos.first << " ";
    fileStream << pos.second << " ";
  }
  
  
  game.setChanged(false);
}


/**
 * @fn loadGame()
 * @brief Loads the game to a textfile.
 * @param game - Reference on a game object
 * 
 * Loads data from a textfile and loads it into a game class.
 */
void FileIO::loadGame (Game& game)
{
  int tmp
  
  game = newGame();
  
  fstream >> turn;
  for (int i=0; i < 5; i++)
    for (int j=0; j < 5; j++)
    {
      fileStream << tmp;
      game.getGrid().getCell(i,j)->setStatus(tmp);
    }
  
  fileStream << tmp;
  game.getTiger().setScore(tmp);
  Tiger** tigers = game.getTiger().getTigers();
  for (int i=0;j<4;j++)
  {
    int x, y;
    fileStream << x;
    fileStream << y;
    tigers[i].setCell(game.getGrid().getCell(x,y);
  }
  fileStream << tmp;
  game.getGoat().setNextGoat(tmp);
  Goat** goats = game.getGoat().getGoats();
  for (int i=0;i<20;i++)
  {
    int x, y;
    fileStream << x;
    fileStream << y;
    goats[i].setCell(game().getGrid().getCell(x,y);
  }
  
    game.setChanged(false);
  }
  
  
  