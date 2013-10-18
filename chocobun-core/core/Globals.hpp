/*
 * This file is part of Chocobun.
 *
 * Chocobun is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Chocobun is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Chocobun.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __CHOCOBUN_GLOBALS_HPP__
#define __CHOCOBUN_GLOBALS_HPP__

// --------------------------------------------------------------
// Globals.hpp
// --------------------------------------------------------------

/*!
 * @brief Global typedefs, constants, or defines used throughout chocobun
 *
 * # Constants #
 * - **validTiles**
 *     > A whitelist of characters that can be considered level tiles.
 *     > This is used to detect level data when loading and parsing levels,
 *     > and is used to validate tiles when manipulating Level objects.
 * - **validUndoData**
 *     > A whitelist of characters that can be considered undo data.
 *     > 
 */

#include <string>

namespace Chocobun {

// forward declarations
template <class T> class Array2D;

// --------------------------------------------------------------
// constants
static const std::string validTiles = "#@+$*. _pPbB";
static const std::string validUndoData = "udlrUDLR";

// --------------------------------------------------------------
// typedefs
typedef Array2D<char> LevelArray_t;

} // namespace Chocobun

#endif // __CHOCOBUN_GLOBALS_HPP__
