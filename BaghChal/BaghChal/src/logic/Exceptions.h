/**
 * @file Exceptions.h
 * @brief Contains all Exceptions ocurring in Game Logic
 * @author Julian Bayer, Steffen Dittmar
 */

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <exception>

using namespace std;

/**
 * @class CanNotMoveException
 * @brief Is thrown on an invalid move
 */

class CanNotMoveException : public exception
{
public: 
  const char* what() const throw(){ return "Ungültiger Spielzug."; }
};

/**
 * @class InvalidStateException
 * @brief Is thrown on trying to assign an invalid state to a cell
 * 
 * State cannot be negative or greater than 2!
 */

class InvalidStateException : public exception
{
public: 
  const char* what() const throw(){ return "Ungültiger Spielstatus."; }
};

/**
 * @brief Is thrown when it's the tiger's turn but a goat is moved or vice versa.
 *
 * The object trying to be moved must be pointet to in the current players Goat or Tiger array.
 */
class InvalidSourceException : public exception
{
public: 
  const char* what() const throw(){ return "Ungültige Spielfigur."; }
};

class InvalidDirectionException : public exception
{
public: 
  const char* what() const throw(){ return "Ungültige Richtung."; }
};

class UnoccupiedCellException : public exception
{
public: 
  const char* what() const throw(){ return "Das Feld ist nicht besetzt."; }
};

class InvalidOccupantException : public exception
{
public: 
  const char* what() const throw(){ return "Spielzug ist nicht erlaubt."; }
};

class OccupiedCellException : public exception
{
public: 
  const char* what() const throw(){ return "Feld ist besetzt."; }
};

/**
 * @brief Is thrown when PlayerGoat has won.
 *
 * The goats turn is finished and no Tiger is able to perform any valid moves.
 */
class GoatWonException : public exception
{
public: 
  const char* what() const throw(){ return "Ziege gewinnt."; }
};

/**
 * @brief Is thrown when PlayerTiger has won.
 *
 * The tigers turn is finished and he has eaten 5 goats.
 */
class TigerWonException : public exception
{
public: 
  const char* what() const throw(){ return "Tiger gewinnt."; }
};

/**
 * @brief Is thrown when PlayerTiger eats a Goat.
 *
 * The tigers turn eats a goat.
 */
class TigerEatGoatException : public exception
{
public: 
  const char* what() const throw(){ return "Tiger hat eine Ziege gefressen."; }
};

/**
 * @brief Is thrown when the GoatPlayer has no more valid moves.
 *
 * The tigers turn is finished and no Goat is able to perform any valid moves.
 */
class GameEvenException : public exception
{
public: 
  const char* what() const throw(){ return "Unentschieden. Keine weitere Züge möglich."; }
};

class InvalidInputFileException : public exception
{
public: 
  const char* what() const throw(){ return "Ungültige Datei."; }
};

#endif
