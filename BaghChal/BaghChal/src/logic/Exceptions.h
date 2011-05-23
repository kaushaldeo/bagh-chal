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
  virtual const char* what() const throw()
  {
    return "This move is invalid";
  }
};

/**
 * @class InvalidStateException
 * @brief Is thrown on trying to assign an invalid state to a cell
 * 
 * State cannot be negative or greater than 2!
 */

class InvalidStateException : public exception
{
  virtual const char* what() const throw()
  {
    return "This is not a valid state";
  }
};

/**
 * @brief Is thrown when it's the tiger's turn but a goat is moved or vice versa.
 *
 * The object trying to be moved must be pointet to in the current players Goat or Tiger array.
 */
class InvalidSourceException : public exception
{
    virtual const char* what() const throw()
    {
        return "This is not a valid source";
    }
};

class InvalidDirectionException : public exception
{
  virtual const char* what() const throw()
  {
    return "This is not a valid direction";
  }
};

class UnoccupiedCellException : public exception
{
  virtual const char* what() const throw()
  {
    return "This cell is not occupied";
  }
};

class InvalidOccupantException : public exception
{
  virtual const char* what() const throw()
  {
    return "This operation is not allowed on this occupant";
  }
};

class OccupiedCellException : public exception
{
  virtual const char* what() const throw()
  {
    return "This cell is occupied.";
  }
};

/**
 * @brief Is thrown when PlayerGoat has won.
 *
 * The goats turn is finished and no Tiger is able to perform any valid moves.
 */
class GoatWonException : public exception
{
    virtual const char* what() const throw()
    {
        return "The Goat has won.";
    }
};

/**
 * @brief Is thrown when PlayerTiger has won.
 *
 * The tigers turn is finished and he has eaten 5 goats.
 */
class TigerWonException : public exception
{
    virtual const char* what() const throw()
    {
        return "The Tiger has won.";
    }
};

/**
 * @brief Is thrown when PlayerTiger eats a Goat.
 *
 * The tigers turn eats a goat.
 */
class TigerEatGoatException : public exception
{
    virtual const char* what() const throw()
    {
        return "The Tiger eat a Goat.";
    }
};

/**
 * @brief Is thrown when the GoatPlayer has no more valid moves.
 *
 * The tigers turn is finished and no Goat is able to perform any valid moves.
 */
class GameEvenException : public exception
{
    virtual const char* what() const throw()
    {
        return "The Game is even.";
    }
};

#endif
