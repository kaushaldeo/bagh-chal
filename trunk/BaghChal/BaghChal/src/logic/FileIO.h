/**
* FileIO
* @file FileIO.h
* @brief Headerfile for File I/O
* @see FileIO
* @author Julian Bayer
*/

#ifndef FILEIO_H
#define FILEIO_H
#include "Game.h"
#include "Enums.h"
#include<string>

/**
 * @class FileIO
 * @brief handles file input and output for saving and loading games
 */
class FileIO
{
public:
    FileIO() : path("bagh-chal-save.txt") {};
    FileIO(std::string filename) : path(filename) {};
    ~FileIO() {};

    /**
     * @fn saveGame()
     * @brief Saves the game to a textfile.
     *
     * Saves the data from game into a textfile.
     */
    void saveGame();

    /**
     * @fn loadGame()
     * @brief Loads the game from a textfile.
     *
     * Loads data from a textfile and loads it into a game class.
     */
    void loadGame();

    /**
     * @fn convertToInt(CellStatus)
     * @param state - CellStatus to be converted to int
     * @brief Converts a member of baghchal::CellStatus into an integer
     * @exception std::exception
     */
    int convertToInt(CellStatus);

    /**
     * @fn convertFromInt(int)
     * @param state - int to be converted to CellStatus
     * @brief Converts an int to a member of baghchal::CellStatus
     * @exception InvalidStateException
     */
    CellStatus convertFromInt(int);

private:
    std::string path; /** < path to savegame */

};
#endif
