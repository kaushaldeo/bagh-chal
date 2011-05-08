#ifndef PLAYERGOAT_H
#define PLAYERGOAT_H

#include "Goat.h"
#include "Cell.h"
#include "Exceptions.h"

/*! \file PlayerGoat.h
 *  \brief Enthält Klasse die den Spieler repräsentiert, der die Ziegen steuert.
 */

//! Klasse die den Spieler repräsentiert, der die Ziegen steuert.
class PlayerGoat
{
public:
    /*! \brief Konstruktor.
     *
     *  Erzeugt 20 Ziegen, ohne diese auf dem Feld zu setzen und initialisiert nextGoat auf 0.
     */
    PlayerGoat();

    /*! \brief Destruktor.
     *
     *  Löscht Ziegen.
     */
    ~PlayerGoat();

    /*! \brief Ruft Goat::setCell() auf.
     *
     *  Wählt ungesetzte Ziege aus und plaziert sie auf cell.
     *
     *  \param cell Zelle, auf die Ziege gesetzt werden soll.
     *  \exception CanNotMoveException Wird geworfen, wenn Zielzelle belegt ist.
     */
    void setCell(Cell *cell);

    /*! \brief Ruft Goat::move() auf.
     *
     *  Ermittelt betreffende Ziege durch Vergleich des übergebenen Cellpointer
     *  mit den 20 Ziegen und ruft die Goat::move()-Funktion auf.
     *
     *  \param src Die Zelle, auf der die Ziege sich befindet.
     *  \param dst Die Zielzelle.
     *  \exception CanNotMoveException Wird geworfen, wenn der Zug ungültig ist.
     */
    void move(Cell*src, Cell *dst);

	void setGoats(Goat** goats);

	Goat** getGoats();

	void setNextGoat(int number);

	int getNextGoat();

private:
    //! Array, das Zeiger auf die 20 Ziegen enthält.
    Goat **goats; //Hallo Steffen, bitte noch getter/setter einfügen, wegen Laden/Speichern, merci! Gruß, Julian

    //! Nächste zu platzierende Ziege im Array
    int nextGoat; //Hallo Steffen, bitte noch getter/setter einfügen, wegen Laden/Speichern, merci! Gruß, Julian
};

#endif
