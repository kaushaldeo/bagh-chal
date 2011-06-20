/**
* Grid class
* @file Grid.cpp
* @brief Implementation for Grid Class
* @see Grid
* @author Julian Bayer
*/

#include "Cell.h"
#include "Grid.h"

/**
 * @fn Grid()
 * @brief Constructs a grid of 5*5 Cells
 *
 * This is the Constructor for the grid.
 */
Grid::Grid() : cells(new Cell **[5])
{
    for (int i = 0; i < 5; i++)
    {
        cells[i] = new Cell*[5];

        for (int j = 0; j < 5; j++)
        {
            cells[i][j] = new Cell(i, j, this);
        }
    }
}

/**
 * @fn ~Grid()
 * @brief Default destructor for grid
 */
Grid::~Grid()
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            delete cells[i][j];
        }

        delete [] cells[i];
    }

    delete [] cells;
}

/**
 * @fn getCell()
 * @brief get a cell by its coordinates
 * @param x - The x coordinate
 * @param y - The y coordinate
 * @returns pointer to the cell in question
 *
 * Get a cell by its x and y coordinates.
 */
Cell *Grid::getCell(int x, int y)
{
    if (x > 4 || y > 4)
    {
        return 0;
    }

    return cells[x][y];
}
