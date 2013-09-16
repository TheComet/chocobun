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
#include <core/Level.hpp>

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
void CollectionParserBase::registerLevel( Level* level, std::string& levelName, std::vector<Level*>& levels )
{
    std::stringstream ss;
    std::vector<Level*>::iterator it;
    if( levelName.size() == 0 )
    {
        Uint32 i = 1;
        do{
            ss.clear();
            ss.str("");
            ss << "Level #";
            ss << i;
            ++i;
            for( it = levels.begin(); it != levels.end(); ++it )
                if( (*it)->getLevelName().compare(ss.str()) == 0 )
                    break;
        }while( it!= levels.end() );
        levelName = ss.str();
    }
    level->setLevelName( levelName );
    levels.push_back( level );
}

// --------------------------------------------------------------
void CollectionParserBase::enableCompression( void )
{
}

// --------------------------------------------------------------
void CollectionParserBase::disableCompression( void )
{
}

} // namespace Sokoban
