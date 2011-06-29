/**
* FileIO
* @file FileIO.cpp
* @brief Implementation file for FileIO Class
* @see FileIO
* @author Julian Bayer
*/
#include "FileIO.h"
#include <fstream>

using namespace std;

void FileIO::saveGame()
{
    Game *game = Game::getInstance();   //Get current game

    ofstream fileStream(path.c_str());                      //Open Output File Stream to file indicated in constructor.
    fileStream << convertToInt(game->getTurn()) << " ";     //Convert the turn-flag to int and write to file.
    Grid &grid = game->getGrid();
    fileStream << game->getTiger().getScore() << " ";       //Write current score of tiger to file
    fileStream << game->getGoat().getNextGoat() << endl;    //Write index of next goat to be set to file and end line

    // Do a loop over all the cells in the game.
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            Cell *cell = grid.getCell(i, j);                //Get a cell
            /*
             * If it's not empty, write its x- and y-coordinate to file, convert status to int and write to file, then end line
             * We only save occupied cells to save space
             */
            if (cell->getStatus() != baghchal::empty)       
            {
                fileStream << i << " " << j << " " << convertToInt(cell->getStatus()) << endl;
            }
        }
    }

    /*
     * We need to mark the end of the file, because we have added std::endl above.
     * When we read the file with std::ifstream::operator>>(), ifstream::eof() will not recognize the end of file, because there's still the endline-Symbol.
     * Because of that we mark the end of the savegame with the number 1024
     */
    fileStream << 1024;
    game->setChanged(false);    //Mark game as unchanged since last save.
    fileStream.close();         //Close file stream
}

void FileIO::loadGame()
{
    ifstream fileStream(path.c_str());      //Open an input file stream from file indicated in constructor
    int tmp;                                //Temporary int variable for read-operations
    Game *game = Game::getInstance();       //Get game instance...
    game->startNewGame();                   // ... and start a new game.
    fileStream >> tmp;                      //read first number from file
    game->setTurn(convertFromInt(tmp));     //convert read number to baghchal::CellStatus and set turn of game instance.
    fileStream >> tmp;                      //read next number
    game->getTiger().setScore(tmp);         //set score
    fileStream >> tmp;
    game->getGoat().setNextGoat(tmp);       //set index of next goat to be set


    Tiger **tigers = game->getTiger().getTigers();  //Get Array of tigers
    Goat **goats = game->getGoat().getGoats();      //Get array of goats
    int goatCounter = game->getTiger().getScore();  //Count goats, beginning at the score (because those have already been set AND taken out of the game
    int tigerCounter = 0;                           //Count tigers

    // We have started a ner game, so we need to remove the tigers from the grid, because they're in the corners.
    for (int i = 0; i < 4; i++)
    {
        tigers[i]->getCell()->removeTiger();
    }

    /*
     * Now, we read the occupied cells from the file.
     */
    while (true)   
    {
        if (fileStream.eof())   //If we encounter the end of file prematurely, we throw an exception
        {
            throw new InvalidInputFileException();
        }

        int x;              //x-coordinate
        int y;              //y-coordinate
        int istatus;        //Integer representation of the cell's status.
        fileStream >> x;    //Read x-coordinate

        if (x == 1024)      //If we read the number 1024, we have reached the end of input (see saveGame())
        {
            break;
        }

        /*
         * If we encounter the end of file prematurely, 
         * if we read a fifth tiger,
         * or if we have more goats than we should have,
         * we throw an exception.
         * 
         * If the next goat to be set doesn't have index 0 and our goatCounter is larger than that index, we have more goats, than we should have.
         */
        if (fileStream.eof() || tigerCounter > 4 || (game->getGoat().getNextGoat() != 0 && goatCounter > game->getGoat().getNextGoat()))
        {
            throw new InvalidInputFileException();
        }

        fileStream >> y;    //Read y-coordinate

        if (fileStream.eof())   //If we encounter the end of file prematurely, we throw an exception
        {
            throw new InvalidInputFileException();
        }

        fileStream >> istatus;  //Read status
  
        if (fileStream.eof())   //If we encounter the end of file prematurely, we throw an exception
        {
            throw new InvalidInputFileException();
        }

        baghchal::CellStatus status = convertFromInt(istatus);  //convert istatus to baghchal::CellStatus

        /*
         * If one of the coordinates is larger than 5, or the cell is not occupied, we throw an exception
         */
        if (x >= 5 || y >= 5 || status == baghchal::empty)
        {
            throw new InvalidInputFileException();
        }

        Cell *cell = game->getGrid().getCell(x, y);     //Get the cell  at the read coordinates
        cell->setStatus(convertFromInt(istatus));       //set its status

        if (status == baghchal::tiger)                      //If it's occupied by a tiger...
        {
            tigers[tigerCounter]->setCell(cell);            //Set the next tigers cell
            cell->overrideTiger(tigers[tigerCounter]);      //Override the cells tiger pointer to the next tiger (ignoring the cells current staus)
            tigerCounter++;                                 //increment the counter
        }
        else if (status == baghchal::goat)                  //If it's occupied by a goat
        {
            goats[goatCounter]->setCell(cell);              //Set the next goats cell
            cell->overrideGoat(goats[goatCounter]);         //Override the cells goat pointer to the next goat (ignoring the cells current staus)
            goatCounter++;                                  //increment the counter
        }
    }   //And read the next cell

    game->setChanged(false);    //game has not changed since last load.
    fileStream.close();         //close the file stream.
}

CellStatus FileIO::convertFromInt(int state)
{
    switch (state)
    {
    case 0:
        return empty;
    case 1:
        return tiger;
    case 2:
        return goat;
    default:
        throw new InvalidStateException();
    }
}

int FileIO::convertToInt(CellStatus state)
{
    switch (state)
    {
    case empty:
        return 0;
    case tiger:
        return 1;
    case goat:
        return 2;
    }

    throw new exception();
}
