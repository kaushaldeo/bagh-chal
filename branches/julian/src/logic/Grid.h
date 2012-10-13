/**
* Grid class
* @file Grid.h
* @brief Headerfile for Grid Class
* @see Grid
* @author Julian Bayer
*/
#ifndef GRID_H
#define GRID_H
//#include "Test.h" //This is for Test purposes only and must be removed when compiling the whole Game!

class Cell;

/**
* @class Grid
* @brief Class of the playing field
*
* The Grid class controls the 5*5 playing field.
*/
class Grid
{
public:
    /**
     * @fn Grid()
     * @brief Constructs a grid of 5*5 Cells
     *
     * This is the Constructor for the grid.
     */
    Grid();

    /**
     * @fn ~Grid()
     * @brief Default destructor for grid
     */
    ~Grid();

    /**
     * @fn *getCell(int x, int y)
     * @brief get a cell by its coordinates
     * @param x - The x coordinate
     * @param y - The y coordinate
     * @returns pointer to the cell in question
     *
     * Get a cell by its x and y coordinates.
     */
    Cell *getCell(int x, int y);

private:
    Cell *** cells;   /**< Pointer to a 5x5-array of Cell-Object-Pointers, represents the 25 fields on the grid */

};

#endif
