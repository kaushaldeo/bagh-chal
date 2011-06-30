/**
 * @file Enums.h
 * @brief Enumerations for directions and cell status
 * @author Steffen Dittmar
 */
#ifndef ENUMS_H
#define ENUMS_H

/**
 * @brief Namespace used for enums
 */
namespace baghchal
{
/**
 * @brief Enumaration for directions
 */
enum Direction
{
    right,		/**< right */
    below,		/**< below */
    left,		/**< left */
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
}

#endif
