/*
 * This file is part of Sokoban.
 *
 * Sokoban is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Sokoban is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Sokoban.  If not, see <http://www.gnu.org/licenses/>.
 */

// --------------------------------------------------------------
// include files

#include <core/Config.hpp>
#include <core/CollectionParserBase.hpp>

#include <sstream>

namespace Sokoban {

// --------------------------------------------------------------
CollectionParserBase::CollectionParserBase( void )
{
}

// --------------------------------------------------------------
CollectionParserBase::~CollectionParserBase( void )
{
}

// --------------------------------------------------------------
void CollectionParserBase::registerLevel( Level* level, std::string& levelName, std::map<std::string, Level*>& levelMap )
{
    std::stringstream ss;
    if( levelName.size() == 0 )
    {
        Uint32 i = 1;
        do{
            ss.clear();
            ss.str("");
            ss << "Level #";
            ss << i;
            ++i;
        }while( levelMap.find(ss.str()) != levelMap.end() );
        levelName = ss.str();
    }
    levelMap[levelName] = level;
}

} // namespace Sokoban
