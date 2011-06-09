/**
* Grid class
* @file Grid.cpp
* @brief Implementation for Grid Class
* @see Grid
* @author Julian Bayer
*/

#include "Grid.h"
#include "Cell.h"

/**
 * @fn Grid()
 * @brief Constructs a Grid of 5*5 Cells
 * 
 * Constructor for Grid
 */
Grid::Grid () : cells (new Cell**[5])
{
  for (int i=0; i < 5; i++)
  {
    cells[i] = new Cell*[5];
    for (int j=0; j < 5; j++)
    {
      cells[i][j] = new Cell (i,j, this);
    }
  }
}

/**
 * @fn ~Grid()
 * @brief Default destructor for Grid
 */
Grid::~Grid ()
{
  for (int i=0; i<5; i++)
  {
    for (int j=0; j<5; j++)
      delete cells[i][j];
    delete [] cells[i];
  }
  delete [] cells;
}

/**
 * @fn getCell()
 * @brief get a Cell by its coordinates
 * @param x the x coordinate
 * @param y the y coordinate
 * @returns pointer to the cell in question
 * 
 * Get a cell by its x and y coordinates
 */
Cell* Grid::getCell(int x, int y)
{
  if (x > 4 || y > 4)
    return 0; //again an exception would be the better solution
  return cells[x][y];
}