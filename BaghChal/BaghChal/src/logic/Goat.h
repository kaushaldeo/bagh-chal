#ifndef GOAT_H
#define GOAT_H

#include "Cell.h"
#include "Exceptions.h"
#include "Enums.h"

/** @file Goat.h
 *  @brief Headerfile for goat class
 *  @author Steffen Dittmar
 */

/**
 * @brief Class representing a single goat in the logic layer
 */
class Goat
{
public:
    Goat();
    void setCell(Cell *cell);
    void removeCell();
    bool canMove();
    Cell *getCell();
    bool canMoveThere(Cell *cell);
    void move(Cell *cell);

private:
    Cell *cellPtr;			/**< Pointer to the cell the goat resides on */
};

#endif
