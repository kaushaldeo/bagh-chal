#ifndef PLAYERTIGER_H
#define PLAYERTIGER_H 

#include "Tiger.h"
#include "Cell.h"
#include "Exceptions.h"

/*! \file PlayerTiger.h
 *  \brief Enthält Klasse die den Spieler repräsentiert, der die Tiger steuert.
 */

//! Klasse die den Spieler repräsentiert, der die Tiger steuert.
class PlayerTiger
{
public:

	PlayerTiger() {}

	/*! \brief Konstruktor.
	 *
	 *  Erzeugt 4 neue Tiger und setzt sie auf die übergebenen Eckfelder.
	 *  Initialisiert score auf 0.
	 *
	 *  \param tigerCells Array mit Zeigern auf die 4 Eckfelder.
	 */
	PlayerTiger(Cell *tigerCells[]);

	/*! \brief Destruktor.
	 *
	 *  Löscht Tiger.
	 */
	~PlayerTiger();

	/*! \brief Überprüft, ob noch Züge möglich sind.
	 * 
	 *  Ruft Tiger::canMove() aller 4 Tiger auf.
	 *  
	 *  \return True, wenn noch Züge möglich sind, sonst false.
	 */
	bool canMove();

	/*! \brief Ruft Tiger::move() auf.
	 *
	 *  Ermittelt betreffenden Tiger durch Vergleich des übergebenen Cellpointer
	 *  mit den 4 Tigern und ruft die Tiger::move()-Funktion auf.
	 *
	 *  \param src Die Zelle, auf der der Tiger sich befindet.
	 *  \param dst Die Zielzelle.
	 *  \exception CanNotMoveException Wird geworfen, wenn der Zug ungültig ist.
	 *  \return 1, wenn eine Ziege gefressen wurde, 0 sonst.
	 */
	void move(Cell *src, Cell *dst);

	void setScore(int score);

	int getScore();

	void setTigers(Tiger **tigers);

	Tiger** getTigers();

private:


	//! Array, das Zeiger auf die 4 Tiger enthält.
	Tiger **tigers;

	//! Anzahl der gefressenen Ziegen.
	int score;  
    

};

#endif
