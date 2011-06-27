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

    /**
    * @fn getStatus()
    * @brief Get Status of Cell
    * @returns int Status: 0 = empty, 1 = tiger, 2 = goat
    *
    * Get the status of the cell.
    */
    CellStatus getStatus();

    /**
    * @fn getPosition()
    * @brief Get Position of cell on grid
    * @returns std::pair\<int, int> with first as x-position and second as y-position
    *
    * Get the position of the cell on grid.
    */
    std::pair<int, int> getPosition();

    /**
    * @fn getNeighbor()
    * @brief Get neighboring cell on grid as indicated by direction
    * @param direction - member of baghchal::Direction indicating direction
    * @exception CanNotMoveException
    *
    * The function checks wether there is a neighbor as indicated by the direction.
    * If there is none, the function throws a CanNotMoveException.
    */
    Cell *getNeighbor(Direction);

    /**
     * @fn setStatus()
     * @brief Sets the status of the cell
     * @param newState - unsigned integer value indicating the new status
     */
    void setStatus(CellStatus);

    /**
     * @fn getTiger()
     * @brief Gets tiger
     * @returns Tiger*
     * @exception UnoccupiedCellException
     * @exception InvalidOccupantException
     *
     * Returns a pointer on tiger currently occupying this cell.
     * Throws UnoccupiedCellException if the cell is unoccupied.
     * Throws InvalidOccupantException if the cell is occupied by a goat.
     */
    Tiger *getTiger();

    /**
     * @fn getGoat()
     * @brief Gets the occupying goat
     * @returns Goat*
     * @exception UnoccupiedCellException
     * @exception InvalidOccupantException
     *
     * Returns a pointer on goat currently occupying this cell.
     * Throws UnoccupiedCellException if the cell is unoccupied.
     * Throws InvalidOccupantException if the cell is occupied by a tiger.
     */
    Goat *getGoat();

    /**
     * @fn setTiger()
     * @brief Sets Tiger
     * @exception OccupiedCellException
     *
     * Sets tigerPtr to a pointer on the tiger currently occupying the cell.
     * If the cell is already occupied, throws OccupiedCellException.
     */
    void setTiger(Tiger *);

    /**
     * @fn setGoat()
     * @brief Sets new goat
     * @exception OccupiedCellException
     *
     * Sets goatPtr to a pointer on the goat currently occupying the cell.
     * If the cell is already occupied, throws OccupiedCellException.
     */
    void setGoat(Goat *);

    /**
     * @fn overrideTiger()
     * @brief Override tiger
     *
     * Sets tigerPtr to a pointer on the tiger currently occupying the cell.
     * Ignores status of cell!
     */
    void overrideTiger(Tiger *);

    /**
     * @fn overrideGoat()
     * @brief Override goat
     *
     * Sets goatPtr to a pointer on the goat currently occupying the cell.
     * Ignores status of cell!
     */
    void overrideGoat(Goat *);

    /**
     * @fn removeGoat()
     * @brief Removes goat from cell
     * @exception UnoccupiedCellException
     * @exception InvalidOccupantException
     *
     * Removes goat from cell.
     * Throws UnoccupiedCellException if the cell is unoccupied.
     * Throws InvalidOccupantException if the cell is occupied by a tiger.
     */
    void removeGoat();

    /**
     * @fn removeTiger()
     * @brief Removes tiger from cell
     * @exception UnoccupiedCellException
     * @exception InvalidOccupantException
     *
     * Removes tiger from cell.
     * Throws UnoccupiedCellException if the cell is unoccupied.
     * Throws InvalidOccupantException if the cell is occupied by a goat.
     */
    void removeTiger();

    /**
     * @fn isNeighbor()
     * @brief Tests, if a cell is neighbor to this cell
     * @returns Direction - direction of the cell
     * @param cell - The cell to be tested
     * @see getNeighbor()
     * @exception InvalidDirectionException
     *
     * Checks whether the cell is neighbour of this cell, using getNeighbor().
     */
    Direction isNeighbor(Cell *);

    /**
     * @fn isJumpOverNeighbor()
     * @brief Tests, if a cell is a neighboring cell of a cell containing a goat and neighboring this
     *  cell in the same direction
     * @returns int - direction of the cell
     * @param cell - The cell to be tested
     * @see getNeighbor()
     * @exception InvalidDirectionException
     *
     * The function uses getNeighbor().
     */
    Direction isJumpOverNeighbor(Cell *);

private:
    Cell();                         /**< This is private because a default constructor is not necessary and in fact would make no sense at all */
    CellStatus status;              /**< This represents the status of the field. It can be neutral (0), tiger (1) or goat (2) */
    int positionX;                  /**< This is the X coordinate of the cell */
    int positionY;                  /**< This is the Y coordinate of the cell */
    Grid *grid;                     /**< This is a pointer to the grid */

    /**
     * @fn canMoveDiagonally()
     * @brief Tests, if player can move diagonally from this cell
     * @returns bool
     *
     * A piece can move diagonally if both his coordinates are odd or if both are even.
     * If this is not the case, a diagonal move is not permitted.
     */
    bool canMoveDiagonally();
    CanNotMoveException moveEx;     /**< CanNotMoveException */
    UnoccupiedCellException uOcEx;  /**< UnoccupiedCellException */
    InvalidOccupantException iOcEx; /**< InvalidOccupantException */
    OccupiedCellException ocEx;     /**< OccupiedCellException */
    Tiger *tigerPtr;                /**< Tiger occupying the cell */
    Goat *goatPtr;                  /**< Goat occupying the cell */

};

#endif
