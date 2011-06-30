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
    //Do a loop over cells
    for (int i = 0; i < 5; i++)
    {
        //and create an array of 5 cell-pointers at every line
        cells[i] = new Cell*[5];

        // Do a loop over those cells
        for (int j = 0; j < 5; j++)
        {
            cells[i][j] = new Cell(i, j, this); //And create the cells
        }
    }
}

Grid::~Grid()
{
    //Do a loop over every line of cells
    for (int i = 0; i < 5; i++)
    {
        //Do a loop over every cell-pointer in the line
        for (int j = 0; j < 5; j++)
        {
            delete cells[i][j];     //free memory
        }

        delete [] cells[i]; //free memory for each line
    }

    delete [] cells;    //and lastly: free memory of cells
}

Cell *Grid::getCell(int x, int y)
{
    if (x > 4 || y > 4) //If the coordinates are invalid, return Null-pointer
    {
        return 0;
    }

    return cells[x][y];
}
