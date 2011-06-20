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
#include "Enums.h"

class Tiger;
class Goat;

using namespace baghchal;

/**
* @class Cell
* @brief Class of the single cell on the playing field
*
* The Cell class represents a single field on the playing field and can be taken by either a tiger or a goat or can be neutral.
*/
class Cell
{
public:
    Cell(int x, int y, Grid *gridPtr) : status(empty), positionX(x), positionY(y), grid(gridPtr), tigerPtr(0), goatPtr(0) {};
    ~Cell() {};
    CellStatus getStatus();
    std::pair<int, int> getPosition();
    Cell *getNeighbor(Direction);
    void setStatus(CellStatus);
    Tiger *getTiger();
    Goat *getGoat();
    void setTiger(Tiger *);
    void setGoat(Goat *);
    void overrideTiger(Tiger *);
    void overrideGoat(Goat *);
    void removeGoat();
    void removeTiger();
    Direction isNeighbor(Cell *);
    Direction isJumpOverNeighbor(Cell *);

private:
    Cell();         // This is private because a default constructor is not necessary and in fact would make no sense at all
    CellStatus status;              /**< This represents the status of the field. It can be neutral (0), tiger (1) or goat (2) */
    int positionX;                  /**< This is the X coordinate of the cell */
    int positionY;                  /**< This is the Y coordinate of the cell */
    Grid *grid;                     /**< This is a pointer to the grid */
    bool canMoveDiagonally();
    CanNotMoveException moveEx;     /**< CanNotMoveException */
    UnoccupiedCellException uOcEx;  /**< UnoccupiedCellException */
    InvalidOccupantException iOcEx; /**< InvalidOccupantException */
    OccupiedCellException ocEx;     /**< OccupiedCellException */
    Tiger *tigerPtr;                /**< Tiger occupying the cell */
    Goat *goatPtr;                  /**< Goat occupying the cell */

};

#endif
