/**
 * @file Exceptions.h
 * @brief Contains all Exceptions ocurring in Game Logic
 * @author Julian Bayer, Steffen Dittmar
 */

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
/**
 * @class CanNotMoveException
 * @brief Is thrown on an invalid move
 */

class CanNotMoveException : public Exception
{
  virtual const char* what() const throw()
  {
    return "This move is invalid";
  }
};
#endif