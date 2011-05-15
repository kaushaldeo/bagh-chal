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
#include<string>

class FileIO
{
  public:
    FileIO () : fileStream("~/bagh-chal-save") {};
    FileIO (std::string filename) : fileStream(filename.c_str()) {};
    ~FileIO ();
    void saveGame(Game&);
    void loadGame(Game&);
  
  private:
    std::fstream fileStream; /**< File Stream for I/O */
};
#endif
