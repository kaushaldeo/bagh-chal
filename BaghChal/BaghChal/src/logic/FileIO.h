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
    void saveGame();
    void loadGame();
    int convertToInt(CellStatus);
    CellStatus convertFromInt(int);

private:
    std::string path; /** < path to savegame */

};
#endif
