/**
* Cell class
* @file Cell.cpp
* @brief Implementation for Cell Class
* @see Cell
* @author Julian Bayer
*/

#include "Cell.h"
#include "Exceptions.h"
#include "Goat.h"
#include "Tiger.h"

/**
* @fn getStatus()
* @brief Get Status of Cell
* @returns int Status: 0 = empty, 1 = tiger, 2 = goat
* 
* Get Status of Cell
*/
CellStatus Cell::getStatus ()
{
  return status;
}

/**
 * @fn setStatus()
 * @brief Sets the status of the cell
 * @param newState - unsigned integer value indicating the new status
 */
void Cell::setStatus (CellStatus newState)
{
  status = newState;
}


/**
* @fn getPosition()
* @brief Get Position of cell on grid
* @returns std::pair\<int, int> with first as x-position and second as y-position
* 
* Get Position of cell on grid
*/
pair <int, int> Cell::getPosition ()
{
  pair <int, int> pos;
  pos.first = positionX;
  pos.second = positionY;
  return pos;
}

/**
* @fn getNeighbor()
* @brief get neighboring cell on grid as indicated by direction
* @param direction - member of baghchal::Direction indicating direction
* @exception CanNotMoveException
* 
* The function checks wether there is a neighbor as indicated by the direction.
* If there is none, the function throws a CanNotMoveException
*/
Cell* Cell::getNeighbor (Direction direction)
{
  switch (direction)
  {
    case baghchal::right: //Right
      if (positionX == 4)
        throw moveEx;
      return grid->getCell(positionX+1, positionY);
    
    case baghchal::below: //Down
      if (positionY == 4)
        throw moveEx;
      return grid->getCell(positionX, positionY+1);
      
    case baghchal::left: //Left
      if (positionX == 0)
        throw moveEx;
      return grid->getCell(positionX-1, positionY);
      
    case baghchal::above: //Up
      if (positionY == 0)
        throw moveEx;
      return grid->getCell(positionX, positionY-1);
        
    case baghchal::rightAbove: //Right+Up
      if (positionX == 4  || positionY == 0 || !canMoveDiagonally())
        throw moveEx;
      return grid->getCell(positionX+1,positionY-1);
      
    case baghchal::rightBelow: //Right+Down
      if (positionX == 4  || positionY == 4 || !canMoveDiagonally())
        throw moveEx;
      return grid->getCell(positionX+1,positionY+1);      
      
    case baghchal::leftBelow: //Left+Down
      if (positionX == 0  || positionY == 4 || !canMoveDiagonally())
        throw moveEx;
      return grid->getCell(positionX-1,positionY+1);
      
    case baghchal::leftAbove: //Left+Up
      if (positionX == 0  || positionY == 0 || !canMoveDiagonally())
        throw moveEx;
      return grid->getCell(positionX-1,positionY-1);
    default:
      return 0;
  }
}

/**
 * @fn canMoveDiagonally()
 * @brief tests, if player can move diagonally from this cell
 * @returns bool
 * 
 * A piece can move diagonally if both his coordinates are odd or if both are even.
 * If this is not the case, a diagonal move is not permitted
 */
bool Cell::canMoveDiagonally()
{
  return positionX % 2 == positionY % 2;
}

/**
 * @fn getTiger()
 * @brief getsTiger
 * @returns Tiger*
 * @exception UnoccupiedCellException
 * @exception InvalidOccupantException
 * 
 * returns pointer on tiger currently occupying this cell
 * Throws UnoccupiedCellException if the cell is unoccupied
 * Throws InvalidOccupantException if the cell is occupied by a goat
 */
Tiger* Cell::getTiger()
{
  if (status == empty)
    throw uOcEx;
  else if (status == goat)
    throw iOcEx;
  
  return tigerPtr;
}

/**
 * @fn getGoat()
 * @brief gets the occupying goat
 * @returns Goat*
 * @exception UnoccupiedCellException
 * @exception InvalidOccupantException
 *
 * returns pointer on goat currently occupying this cell
 * Throws UnoccupiedCellException if the cell is unoccupied
 * Throws InvalidOccupantException if the cell is occupied by a tiger
 */
Goat* Cell::getGoat()
{
  if (status == empty)
    throw uOcEx;
  else if (status == tiger)
    throw iOcEx;
  
  return goatPtr;
}

/**
 * @fn setTiger()
 * @brief setsTiger
 * @exception OccupiedCellException
 * 
 * sets tigerPtr to a pointer on the tiger currently occupying the cell
 * If the cell is already occupied, throws OccupiedCellException
 */
void Cell::setTiger(Tiger* tiger)
{
  if (status != empty)
    throw ocEx;
  
  this->tigerPtr = tiger;
}

/**
 * @fn overrideTiger()
 * @brief setsTiger
 * 
 * sets tigerPtr to a pointer on the tiger currently occupying the cell
 * Ignores status of Cell!
 */
void Cell::overrideTiger(Tiger* tiger)
{
  this->tigerPtr = tiger;
}

/**
 * @fn setGoat()
 * @brief sets new goat
 * @exception OccupiedCellException
 * 
 * sets goatPtr to a pointer on the goat currently occupying the cell
 * If the cell is already occupied, throws OccupiedCellException
 */
void Cell::setGoat(Goat* goat)
{
  if (status != empty)
    throw ocEx;
  
  this->goatPtr = goat;
}


/**
 * @fn overrideTiger()
 * @brief setsTiger
 * 
 * sets goatPtr to a pointer on the goat currently occupying the cell
 * Ignores status of Cell!
 */
void Cell::overrideGoat(Goat* goat)
{
  this->goatPtr = goat;
}

/**
 * @fn removeGoat()
 * @brief removes goat from cell
 * @exception UnoccupiedCellException
 * @exception InvalidOccupantException
 * 
 * Removes goat from cell.
 * Throws UnoccupiedCellException if the cell is unoccupied
 * Throws InvalidOccupantException if the cell is occupied by a tiger
 */
void Cell::removeGoat()
{
  if (status == empty)
    throw uOcEx;
  if (status == tiger)
    throw iOcEx;
  
  goatPtr = 0;
  status = empty;
}

/**
 * @fn removeTiger()
 * @brief removes tiger from cell
 * @exception UnoccupiedCellException
 * @exception InvalidOccupantException
 * 
 * Removes tiger from cell.
 * Throws UnoccupiedCellException if the cell is unoccupied
 * Throws InvalidOccupantException if the cell is occupied by a goat
 */
void Cell::removeTiger()
{
  if (status == empty)
    throw uOcEx;
  if (status == goat)
    throw iOcEx;
  
  tigerPtr = 0;
  status = empty;
}
  
/**
 * @fn isNeighbor()
 * @brief tests, if a cell is neighbor to this cell
 * @returns Direction - direction of the cell
 * @param cell - The cell to be tested
 * @see getNeighbor()
 * @exception InvalidDirectionException
 * 
 * Checks whether the cell is neighbour of this cell, using getNeighbor()
 */
Direction Cell::isNeighbor(Cell* cell)
{
  Direction allDirections[8] = {baghchal::right, baghchal::below, baghchal::left, baghchal::above, baghchal::rightAbove, baghchal::rightBelow, baghchal::leftBelow, baghchal::leftAbove};
  for (int i=0; i < 8; i++)
  {
    try
    {
      Cell* test = getNeighbor(allDirections[i]);
      if (test == cell)
        return allDirections[i];
      continue;
    }
    catch (CanNotMoveException e)
    {
      continue;
    }
  }
  throw InvalidDirectionException();
}
  
/**
 * @fn isJumpOverNeighbor()
 * @brief tests, if a cell is a neighboring cell of a cell containing a goat and neighboring this
 *  cell in the same direction
 * @returns int - direction of the cell
 * @param cell - The cell to be tested
 * @see getNeighbor()
 * @exception InvalidDirectionException
 * 
 * The function uses getNeighbor
 */
Direction Cell::isJumpOverNeighbor(Cell* cell)
{
  Direction allDirections[8] = {baghchal::right, baghchal::below, baghchal::left, baghchal::above, baghchal::rightAbove, baghchal::rightBelow, baghchal::leftBelow, baghchal::leftAbove};
  for (int i=0; i < 8; i++)
  {
    try
    {
      Cell* test = getNeighbor(allDirections[i]);
      if (test)
      {
        if (test->getStatus() == goat && test->getNeighbor(allDirections[i]) == cell)
        {
          return allDirections[i];
        }
      }
      continue;
    }
    catch (CanNotMoveException e)
    {
      continue;
    }
  }
  throw InvalidDirectionException();
}
  
  
  
