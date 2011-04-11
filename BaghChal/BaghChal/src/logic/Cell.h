/**
* Cell class
* @file Cell.h
* @brief Headerfile for Cell Class
* @see Cell
* @author Julian Bayer
*/
#ifndef CELL_H
#define CELL_H
//#include "Test.h" //This is for Test purposes only and must be removed when compiling the whole Game!
#include "Grid.h"

/**
* @class Cell
* @brief Class of the single cell on the playing field
* 
* The Cell class represents a single field on the playing field and can be taken by either a tiger or a goat or can be neutral
*/
class Cell
{
  public:
    Cell (int x, int y, Grid* gridPtr) : status (0), positionX(x), positionY(y), grid(gridPtr) {};
    ~Cell ();
    unsigned int getStatus ();
    std::pair<int, int> getPosition();
    Cell* getNeighbor (int);
    void setStatus(int);
   
  private:
    Cell ();        // This is private because a default constructor is not necessary and in fact would make no sense at all
    unsigned int status;    /**< This represents the status of the field. It can be neutral (0), Tiger (1) or goat (2) */
    int positionX;          /**< This is the X coordinate of the cell */
    int positionY;          /**< This is the Y coordinate of the cell */
    Grid* grid              /**< This is a pointer to the grid */
    bool canMoveDiagonally ();
    
};

#endif/