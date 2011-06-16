#ifndef TIGER_H
#define TIGER_H

#include "Cell.h"
#include "Goat.h"
#include "Exceptions.h"
#include "Enums.h"

/** @file Tiger.h
 *  @brief Headerfile for Tiger class
 *  @author Steffen Dittmar
 */

/**
 * @brief Class representing a single Tiger in the logic layer
 */
class Tiger
{
public:
    Tiger(Cell *cell);
    bool canMove();
    bool canMoveThere(Cell *cell);
    int move(Cell *cell, bool mustEat);
    Cell *getCell();
    void setCell(Cell *cell);
    bool couldEat();

private:
    Cell *cellPtr;			/**< Pointer to the Cell the tiger resides on */
};


#endif
