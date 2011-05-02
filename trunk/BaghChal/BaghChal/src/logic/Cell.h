/**
* Cell class
* @file Cell.h
* @brief Headerfile for Cell Class
* @see Cell
* @author Julian Bayer
*/
#ifndef CELL_H
#define CELL_H
#include "Grid.h"
#include <utility>
#include "Exceptions.h"

class Tiger;
class Goat;

/**
* @class Cell
* @brief Class of the single cell on the playing field
* 
* The Cell class represents a single field on the playing field and can be taken by either a tiger or a goat or can be neutral
*/
class Cell
{
  public:
    Cell (int x, int y, Grid* gridPtr) : status (0), positionX(x), positionY(y), grid(gridPtr), tiger(0), goat (0) {};
    ~Cell ();
    unsigned int getStatus ();
    std::pair<int, int> getPosition();
    Cell* getNeighbor (int);
    void setStatus(int);
    Tiger* getTiger();
    Goat* getGoat();
    void setTiger(Tiger*);
    void setGoat(Goat*);
    void removeGoat ();
    bool isNeighbor(Cell*);
   
  private:
    Cell ();        // This is private because a default constructor is not necessary and in fact would make no sense at all
    unsigned int status;    /**< This represents the status of the field. It can be neutral (0), Tiger (1) or goat (2) */
    int positionX;          /**< This is the X coordinate of the cell */
    int positionY;          /**< This is the Y coordinate of the cell */
    Grid* grid;              /**< This is a pointer to the grid */
    bool canMoveDiagonally ();
    CanNotMoveException moveEx; /**< CanNotMoveException */
    UnoccupiedCellException uOcEx;
    InvalidOccupantException iOcEx;
    OccupiedCellException ocEx;
    Tiger* tiger;           /**< Tiger occupying the cell */
    Goat* goat;             /**< Goat occupying the cell */
    
};

#endif