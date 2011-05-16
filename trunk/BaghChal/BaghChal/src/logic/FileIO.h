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
#include<fstream>
#include<string>

class FileIO
{
  public:
    FileIO () : fileStream("~/bagh-chal-save") {};
    FileIO (std::string filename) : fileStream(filename.c_str()) {};
    ~FileIO () {};
    void saveGame();
    void loadGame();
    int convertToInt (CellStatus);
    CellStatus convertFromInt (int);
  
  private:
    std::fstream fileStream; /**< File Stream for I/O */
};
#endif
