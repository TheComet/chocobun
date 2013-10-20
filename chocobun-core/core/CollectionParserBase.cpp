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
// CollectionParserBase.cpp
// --------------------------------------------------------------

// --------------------------------------------------------------
// include files

#include <core/Collection.hpp>
#include <core/Config.hpp>
#include <core/CollectionParserBase.hpp>
#include <core/Level.hpp>

#include <sstream>

namespace Chocobun {

// --------------------------------------------------------------
CollectionParserBase::CollectionParserBase( void )
{
}

// --------------------------------------------------------------
CollectionParserBase::~CollectionParserBase( void )
{
}

// --------------------------------------------------------------
// This has been changed to 'generateLevelName' and is provided as an interface
// in CollectionParserInterface.
/*
void CollectionParserBase::_registerLevel( Level* level, std::string& levelName, std::vector<Level*>& levels )
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
}*/

// --------------------------------------------------------------
void CollectionParserBase::parse( std::ifstream& file, Collection& collection )
{

    // left empty for future use
    // anything that needs to be done before or after parsing
    // should be implemented here

    // call overridden parse method
    return this->_parse( file, collection );
}

// --------------------------------------------------------------
void CollectionParserBase::save( std::ofstream& file, const Collection& collection )
{

    // left empty for future use
    // anything that needs to be done before or after saving
    // should be implemented here

    // call overridden save method
    this->_save( file, collection );
}

// --------------------------------------------------------------
void CollectionParserBase::enableCompression( void )
{
    // implemented by derived class
}

// --------------------------------------------------------------
void CollectionParserBase::disableCompression( void )
{
    // implemented by derived class
}

// --------------------------------------------------------------
Uint32 CollectionParserBase::getMaxLevelWidth( void )
{
    return m_MaxLevelWidth;
}

// --------------------------------------------------------------
Uint32 CollectionParserBase::getMaxLevelHeight( void )
{
    return m_MaxLevelHeight;
}

// --------------------------------------------------------------
void CollectionParserBase::convertTilesToConventional( std::string& tiles )
{
    for( std::string::iterator it = tiles.begin(); it != tiles.end(); ++it )
    {
        switch( *it )
        {
            case 'p' : *it = '@'; break;
            case 'P' : *it = '+'; break;
            case 'b' : *it = '$'; break;
            case 'B' : *it = '*'; break;
            case '-' : *it = ' '; break;
            case '_' : *it = ' '; break;
            default: break; // could potentionally throw an exception here
        }                   // because the string wouldn't be valid
    }
}

} // namespace Chocobun
