/**
* Grid class
* @file Grid.cpp
* @brief Implementation for Grid Class
* @see Grid
* @author Julian Bayer
*/
#include "Cell.h"
#include "Grid.h"

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

Cell *Grid::getCell(int x, int y)
{
    if (x > 4 || y > 4)
    {
        return 0;
    }

    return cells[x][y];
}
