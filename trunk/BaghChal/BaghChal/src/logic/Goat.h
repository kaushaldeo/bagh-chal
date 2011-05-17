#ifndef GOAT_H
#define GOAT_H

#include "Cell.h"
#include "Exceptions.h"
#include "Enums.h"

/*! \file Goat.h
 *  \brief Enthält Klasse, die die Ziegen repräsentiert.
 */

//! Klasse, die die Ziegen repräsentiert.
class Goat
{
public:
	/*! \brief Konstruktor.
	 *
	 *  Erzeugt Ziege und setzt cellPtr auf NULL;
	 */
	Goat();

	/*! \brief Plaziert Ziege auf übergebenen Zelle.
	 *
	 *  Prüft, ob Zelle frei ist und plaziert gegebenenfalls die Ziege.
	 *
	 *  \param cell Zelle, auf die Ziege gesetzt werden soll.
	 *  \exception CanNotMoveException Wird geworfen, wenn Zielzelle belegt ist.
	 */
	void setCell(Cell *cell);

    /*! \brief Gibt aktuelle Zelle zurück
     *
     * blablabla englisch bla
     */

	bool canMove();

    Cell* getCell();

	bool canMoveThere(Cell *cell);

	/*! \brief Bewegt Ziege auf übergebene Zelle.
	 *
	 *  Warning, move doesn't do any reliable exception handling anymore,
	 *  never call without calling canMoveThere first.
	 *
	 *  \param cell Zelle, auf die die Ziege bewegt werden soll.
	 *  \exception CanNotMoveException wird geworfen, wenn der Zug ungültig ist.
	 */
	void move(Cell *cell);

private:
	//! Zeiger auf die aktuelle Zelle.
	Cell *cellPtr;
};

#endif