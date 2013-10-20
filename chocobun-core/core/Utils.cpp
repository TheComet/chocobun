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
// TileUtils.cpp
// --------------------------------------------------------------

#include <core/Config.hpp>
#include <core/Utils.hpp>

namespace Chocobun {

const std::string Utils::validTiles = "#@+$*. _pPbB";
const std::string Utils::validTilesRLE = validTiles + "()0123456789|";
const std::string Utils::validUndoData = "udlrUDLR";

// --------------------------------------------------------------
bool Utils::isTileData( const std::string& str )
{
    for( std::size_t i = 0; i != str.size(); ++i )
        if( validTiles.find(str[i]) == std::string::npos )
            return false;
    return true;
}

// --------------------------------------------------------------
bool Utils::isTileData( const char& chr )
{
    return Utils::isTileData( std::string(&chr) );
}

// --------------------------------------------------------------
bool Utils::isTileDataRLE( const std::string& str )
{
    for( std::size_t i = 0; i != str.size(); ++i )
        if( validTilesRLE.find(str[i]) == std::string::npos )
            return false;
    return true;
}

// --------------------------------------------------------------
bool Utils::isTileDataRLE( const char& chr )
{
    return Utils::isTileDataRLE( std::string(&chr) );
}

// --------------------------------------------------------------
bool Utils::isUndoData( const std::string& str )
{
    for( std::size_t i = 0; i != str.size(); ++i )
        if( validUndoData.find(str[i]) == std::string::npos )
            return false;
    return true;
}

// --------------------------------------------------------------
bool Utils::isUndoData( const char& chr )
{
    return Utils::isUndoData( std::string(&chr) );
}

} // namespace Chocobun
