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

// --------------------------------------------------------------
// TileUtils.hpp
// --------------------------------------------------------------

#ifndef __CHOCOBUN_CORE_UTILS_HPP__
#define __CHOCOBUN_CORE_UTILS_HPP__

#include <string>

namespace Chocobun {

class Utils
{
public:

    /*!
     * @brief
     */
    static bool isTileData( const std::string& str );

    /*!
     * @brief
     */
    static bool isTileData( const char& chr );

    /*!
     * @brief
     */
    static bool isTileDataRLE( const std::string& str );

    /*!
     * @brief
     */
    static bool isTileDataRLE( const char& chr );

    /*!
     * @brief
     */
    static bool isUndoData( const std::string& str );

    /*!
     * @brief
     */
    static bool isUndoData( const char& chr );

private:
    static const std::string validTiles;
    static const std::string validTilesRLE;
    static const std::string validUndoData;
};

} // namespace Chocobun

#endif // __CHOCOBUN_CORE_TILE_UTILS_HPP__
