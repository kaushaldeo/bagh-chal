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
enum Direction
{ 
	right = 0,		/**< right */
	below = 1,		/**< below */
	left = 2,		/**< left */
	above = 3,		/**< above */
	rightAbove = 4,		/**< rightAbove */
	rightBelow = 5,		/**< rightBelow */
	leftBelow = 6,		/**< leftBelow */
	leftAbove = 7		/**< leftAbove */
};

/**
* @brief Enumeration for status of a cell
*/
enum CellStatus
{
	empty = 0,		/**< empty */
	tiger = 1,		/**< tiger */
	goat = 2		/**< goat */
};


#endif
