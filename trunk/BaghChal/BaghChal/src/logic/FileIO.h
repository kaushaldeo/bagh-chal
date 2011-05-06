/**
* FileIO
* @file FileIO.h
* @brief Headerfile for File I/O
* @see FileIO
* @author Julian Bayer
*/

#ifndef FILEIO_H
#define FILEIO_H

#include<fstream>

class FileIO
{
  public:
    FileIO () : fstream("~/bagh-chal-save");
    FileIO (string filename) : fstream(filename);
    ~FileIO ();
    void saveGame(Game&);
    void loadGame(Game&);
  
  private:
    std::fstream fileStream; /**< File Stream for I/O */
};
#endif