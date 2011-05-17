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

using namespace std;

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
* @param direction - integer value indicating direction
* @exception CanNotMoveException
* 
* The function checks wether there is a neighbor as indicated by the number.
* If there is none, the function returns a nullpointer.
*/
Cell* Cell::getNeighbor (Direction direction)
{
  switch (direction)
  {
    case right: //Right
      if (positionX == 4)
        throw moveEx;
      return grid->getCell(positionX+1, positionY);
    
    case below: //Down
      if (positionY == 4)
        throw moveEx;
      return grid->getCell(positionX, positionY+1);
      
    case left: //Left
      if (positionX == 0)
        throw moveEx;
      return grid->getCell(positionX-1, positionY);
      
    case above: //Up
      if (positionY == 0)
        throw moveEx;
      return grid->getCell(positionX, positionY-1);
        
    case rightAbove: //Right+Up
      if (positionX == 4  || positionY == 0 || !canMoveDiagonally())
        throw moveEx;
      return grid->getCell(positionX+1,positionY-1);
      
    case rightBelow: //Right+Down
      if (positionX == 4  || positionY == 4 || !canMoveDiagonally())
        throw moveEx;
      return grid->getCell(positionX+1,positionY+1);      
      
    case leftBelow: //Left+Down
      if (positionX == 0  || positionY == 4 || !canMoveDiagonally())
        throw moveEx;
      return grid->getCell(positionX-1,positionY+1);
      
    case leftAbove: //Left+Up
      if (positionX == 0  || positionY == 0 || !canMoveDiagonally())
        throw moveEx;
      return grid->getCell(positionX-1,positionY+1);
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
 */
void Cell::setTiger(Tiger* tiger)
{
  if (status != empty)
    throw ocEx;
  
  this->tigerPtr = tiger;
}

/**
 * @fn setGoat()
 * @brief sets new goat
 * @exception OccupiedCellException
 */
void Cell::setGoat(Goat* goat)
{
  if (status != empty)
    throw ocEx;
  
  this->goatPtr = goat;
}



/**
 * @fn removeGoat()
 * @brief removes goat from cell
 * @exception UnoccupiedCellException
 * @exception InvalidOccupantException
 */
void Cell::removeGoat()
{
  if (status == empty)
    throw uOcEx;
  if (status == tiger)
    throw iOcEx;
  
  //goatPtr->setCell(0);
  goatPtr = 0;
  status = empty;
}

void Cell::removeTiger()
{
  if (status == empty)
    throw uOcEx;
  if (status == goat)
    throw iOcEx;
  
  //tigerPtr->setCell(0);
  tigerPtr = 0;
  status = empty;
}
  
/**
 * @fn isNeighbor()
 * @brief tests, if a cell is neighbor to this cell
 * @returns int - direction of the cell
 * @param cell - The cell to be tested
 * @see getNeighbor()
 * @exception InvalidDirectionException
 * 
 * The function uses getNeighbor
 */
Direction Cell::isNeighbor(Cell* cell)
{
  Direction allDirections[8] = {left, right, below, above, rightAbove, leftAbove, rightBelow, leftBelow};
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
  
  
