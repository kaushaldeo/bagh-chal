/**
 * @file Enums.h
 * @brief Enumerations for directions and cell status
 * @author Steffen Dittmar
 */
#ifndef ENUMS_H
#define ENUMS_H

/**
* @brief Enumeration for Directions
*/

//rightr, leftl needs to be discussed tomorrow
enum Direction
{ 
	rightr,		/**< right */
	below,		/**< below */
	leftl,		/**< left */
	above,		/**< above */
	rightAbove,		/**< rightAbove */
	rightBelow,		/**< rightBelow */
	leftBelow,		/**< leftBelow */
	leftAbove		/**< leftAbove */
};

/**
* @brief Enumeration for status of a cell
*/
enum CellStatus
{
	empty,		/**< empty */
	tiger,		/**< tiger */
	goat		/**< goat */
};


#endif
