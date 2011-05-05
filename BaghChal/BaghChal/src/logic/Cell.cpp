/**
* Cell class
* @file Cell.cpp
* @brief Implementation for Cell Class
* @see Cell
* @author Julian Bayer
*/

#include "Cell.h"
#include "Exceptions.h"

using namespace std;

/**
* @fn getStatus()
* @brief Get Status of Cell
* @returns int Status: 0 = neutral, 1 = tiger, 2 = goat
* 
* Get Status of Cell
*/
unsigned int Cell::getStatus ()
{
  return status;
}

/**
 * @fn setStatus()
 * @brief Sets the status of the cell
 * @param newState - unsigned integer value indicating the new status
 */
void Cell::setStatus (unsigned int newState)
{
  if (newState > 2)
    throw new InvalidStateException()
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
Cell* Cell::getNeighbor (int direction)
{
  switch (direction)
  {
    case 0: //Right
      if (positionX == 4)
        throw moveEx;
      return grid->getCell(positionX+1, positionY);
    
    case 1: //Down
      if (positionY == 4)
        throw moveEx;
      return grid->getCell(positionX, positionY+1);
      
    case 2: //Left
      if (positionX == 0)
        throw moveEx;
      return grid->getCell(positionX-1, positionY);
      
    case 3: //Up
      if (positionY == 0)
        throw moveEx;
      return grid->getCell(positionX, positionY-1);
        
    case 4: //Right+Up
      if (positionX == 4  || positionY == 0 || !canMoveDiagonally())
        throw moveEx;
      return grid->getCell(positionX+1,positionY-1);
      
    case 5: //Right+Down
      if (positionX == 4  || positionY == 4 || !canMoveDiagonally())
        throw moveEx;
      return grid->getCell(positionX+1,positionY+1);      
      
    case 6: //Left+Down
      if (positionX == 0  || positionY == 4 || !canMoveDiagonally())
        throw moveEx;
      return grid->getCell(positionX-1,positionY+1);
      
    case 7: //Left+Up
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
  if (status == 0)
    throw uOcEx;
  else if (status == 2)
    throw iOcEx;
  
  return tiger;
}

/**
 * @fn getGoat()
 * @brief gets the occupying goat
 * @returns Goat*
 * @exception UnoccupiedCellException
 * @exception InvalidOccupantException
 */
Tiger* Cell::getGoat()
{
  if (status == 0)
    throw uOcEx;
  else if (status == 1)
    throw iOcEx;
  
  return goat;
}

/**
 * @fn setTiger()
 * @brief setsTiger
 * @exception OccupiedCellException
 */
void Cell::setTiger(Tiger* tiger)
{
  if (status != 0)
    throw ocEx;
  
  this->tiger = tiger;
}

/**
 * @fn setGoat()
 * @brief sets new goat
 * @exception OccupiedCellException
 */
void Cell::setGoat(Goat* goat)
{
  if (status != 0)
    throw ocEx;
  
  this->goat = goat;
}



/**
 * @fn removeGoat()
 * @brief removes goat from cell
 * @exception UnoccupiedCellException
 * @exception InvalidOccupantException
 */
void Cell::removeGoat()
{
  if (status == 0)
    throw uOcEx;
  if (status == 1)
    throw iOcEx;
  
  goat->setCell(0);
  goat = 0;
  status = 0;
}
  
/**
 * @fn isNeighbor()
 * @brief tests, if a cell is neighbor to this cell
 * @returns int - direction of the cell
 * @param cell - The cell to be tested
 * @see getNeighbor()
 * @throws InvalidDirectionException
 * 
 * The function uses getNeighbor
 */
int Cell::isNeighbor(Cell* cell)
{
  for (int i=0; i < 8; i++)
  {
    try
    {
      Cell* test = getNeighbor(i);
      if (test == cell)
        return i;
      continue;
    }
    catch (CanNotMoveException e)
    {
      continue;
    }
  }
  throw InvalidDirectionException();
}
  
  