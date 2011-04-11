/**
* Grid class
* @file Grid.h
* @brief Headerfile for Grid Class
* @see Grid
* @author Julian Bayer
*/
#ifndef GRID_H
#define GRID_H
//#include "Test.h" //This is for Test purposes only and must be removed when compiling the whole Game!

class Cell;

/**
* @class Grid
* @brief Class of the playing field
* 
* The Grid class controls the 5*5 Playing field
*/
class Grid
{
  public:
    Grid ();
    ~Grid ();
    Cell* getCell (int, int);
   
  private:
    Cell*** cells;    /**< Pointer to a 5x5-array of Cell-Object-Pointers, represents the 25 fields on the grid */
    
};

#endif