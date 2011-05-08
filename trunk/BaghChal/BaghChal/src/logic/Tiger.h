#ifndef TIGER_H
#define TIGER_H

#include "Cell.h"
#include "Exceptions.h"
#include "Enums.h"

/*! \file Tiger.h
 *  \brief Enthält Klasse, die die Tiger repräsentiert.
 */

//! Klasse, die die Tiger repräsentiert.
class Tiger
{
public:
	/*! \brief Konstruktor
	 *
	 *  Setzt neu erzeugten Tiger auf Cell.
	 *
	 *  \param cell Startzelle, auf der der Tiger plaziert wird.
	 */
	Tiger(Cell *cell);

	/*! \brief Überprüft, ob für diesen Tiger noch Züge möglich sind.
	 *  
	 *  \return True, wenn noch Züge möglich sind, sonst false.
	 */
	bool canMove();

	/*! \brief Bewegt Tiger auf übergebene Zelle.
	 *
	 *  Überprüft, ob Zug möglich ist und bewegt gegebenenfalls den Tiger.
	 *
	 *  \param cell Zelle, auf die der Tiger bewegt werden soll.
	 *  \exception CanNotMoveException wird geworfen, wenn der Zug ungültig ist.
	 *  \return 1, wenn Ziege gefressen wurde, 0 sonst.
	 */
	int move(Cell *cell);

	Cell * getCell();

	void setCell(Cell *cell);

private:
	//!Zeiger auf die aktuelle Zelle.
	Cell *cellPtr; //Hallo Steffen, bitte noch getter/setter einfügen, wegen Laden/Speichern, merci! Gruß, Julian
};


#endif
