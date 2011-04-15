#include "Goat.h"

Goat::Goat()
{
	cellPtr = NULL;
}

void Goat::setCell(Cell *cell)
{
	if(cell == NULL || cell->getStatus() != 0)
		throw new CanNotMoveException();

	try
	{
		cell.setStatus(0);
	}
	catch(InvalidStateException e)
	{
		throw e;
	}

	cellPtr = cell;
}

Cell* Goat::getCell();
{
    return cellPtr;
}

void Goat::move(Cell *cell)
{

}

