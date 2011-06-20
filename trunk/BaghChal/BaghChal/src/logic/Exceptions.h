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
 * @extends std::exception
 */

class CanNotMoveException : public exception
{
public:
    const char *what() const throw()
    {
        return "Ungültiger Spielzug.";
    }
};

/**
 * @class InvalidStateException
 * @brief Is thrown on trying to assign an invalid state to a cell
 * @extends std::exception
 */

class InvalidStateException : public exception
{
public:
    const char *what() const throw()
    {
        return "Ungültiger Spielstatus.";
    }
};

/**
 * @class InvalidSourceException
 * @brief Is thrown when it's the tiger's turn but a goat is moved or vice versa.
 * @extends std::exception
 *
 * The object trying to be moved must be pointet to in the current players goat or tiger array.
 */
class InvalidSourceException : public exception
{
public:
    const char *what() const throw()
    {
        return "Ungültige Spielfigur.";
    }
};

/**
 * @class InvalidDirectionException
 * @brief Is thrown if an invalid direction is specified, or if an integer not representing a direction is used
 * @extends std::exception
 */
class InvalidDirectionException : public exception
{
public:
    const char *what() const throw()
    {
        return "Ungültige Richtung.";
    }
};


/**
 * @class UnoccupiedCellException
 * @brief Is thrown on trying to use an operation requiring the cell to be occupied on an unoccupied cell
 * @extends std::exception
 */
class UnoccupiedCellException : public exception
{
public:
    const char *what() const throw()
    {
        return "Das Feld ist nicht besetzt.";
    }
};

/**
 * @class InvalidOccupantException
 * @brief Is thrown on trying to use a goat-operation on a tiger or vice versa
 * @extends std::exception
 */
class InvalidOccupantException : public exception
{
public:
    const char *what() const throw()
    {
        return "Spielzug ist nicht erlaubt.";
    }
};

/**
 * @class OccupiedCellException
 * @brief Is thrown on trying to use an operation requiring the cell to be unoccupied on an occupied cell
 * @extends std::exception
 */
class OccupiedCellException : public exception
{
public:
    const char *what() const throw()
    {
        return "Feld ist besetzt.";
    }
};

/**
 * @class GoatWonException
 * @brief Is thrown when PlayerGoat has won
 * @extends std::exception
 *
 * The goats turn is finished and no tiger is able to perform any valid moves.
 */
class GoatWonException : public exception
{
public:
    const char *what() const throw()
    {
        return "Ziege gewinnt.";
    }
};

/**
 * @class TigerWonException
 * @brief Is thrown when PlayerTiger has won
 * @extends std::exception
 *
 * The tigers turn is finished and he has eaten 5 goats.
 */
class TigerWonException : public exception
{
public:
    const char *what() const throw()
    {
        return "Tiger gewinnt.";
    }
};

/**
 * @class TigerEatGoatException
 * @brief Is thrown when PlayerTiger eats a goat
 * @extends std::exception
 *
 * The tigers turn eats a goat.
 */
class TigerEatGoatException : public exception
{
public:
    const char *what() const throw()
    {
        return "Tiger hat eine Ziege gefressen.";
    }
};

/**
 * @class GameEvenException
 * @brief Is thrown when the GoatPlayer has no more valid moves
 * @extends std::exception
 *
 * The tigers turn is finished and no goat is able to perform any valid moves.
 */
class GameEvenException : public exception
{
public:
    const char *what() const throw()
    {
        return "Unentschieden. Keine weitere Züge möglich.";
    }
};

/**
 * @class InvalidInputFileException
 * @brief Is thrown while trying to read a savegame that is invalid, e.g. falsified
 * @extends std::exception
 */
class InvalidInputFileException : public exception
{
public:
    const char *what() const throw()
    {
        return "Ungültige Datei.";
    }
};

/**
 * @class MustEatException
 * @brief Is thrown when a tiger can eat a goat
 */
class MustEatException : public exception
{
public:
    const char *what() const throw()
    {
        return "Ziege muss gefressen werden.";
    }
};
#endif
