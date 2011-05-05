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
class InvalidSourceException : public Exception
{
    virtual const char* what() const throw()
    {
        return "This is not a valid source";
    }
};

class InvalidDirectionException : public Exception
{
  virtual const char* what() const throw()
  {
    return "This is not a valid direction";
  }
};

#endif
