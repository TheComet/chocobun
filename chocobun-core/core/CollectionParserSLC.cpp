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
// SLC parser
// --------------------------------------------------------------

// --------------------------------------------------------------
// include files

#include <core/CollectionParserSLC.hpp>
#include <core/Level.hpp>

#include <fstream>
#include <sstream>
#include <algorithm>

namespace Chocobun {

// --------------------------------------------------------------
CollectionParserSLC::CollectionParserSLC( void )
{
}

// --------------------------------------------------------------
CollectionParserSLC::~CollectionParserSLC( void )
{
}

// --------------------------------------------------------------
std::string CollectionParserSLC::parse( std::ifstream& file, std::vector<Level*>& levels )
{
    return "";
}

// --------------------------------------------------------------
void CollectionParserSLC::save( const std::string& collectionName, std::ofstream& file, std::vector<Level*>& levels )
{
}

} // namespace Chocobun
