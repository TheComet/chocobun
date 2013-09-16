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
// Level
// --------------------------------------------------------------

// --------------------------------------------------------------
// include files

#include <core/Level.hpp>
#include <core/Exception.hpp>

#include <iostream>

const std::string Sokoban::Level::validTiles = "#@+$*. _pPbB";

namespace Sokoban {

// --------------------------------------------------------------
Level::Level( void )
{
    m_LevelArray.push_back( std::vector<char>(0) );
}

// --------------------------------------------------------------
Level::~Level( void )
{
}

// --------------------------------------------------------------
void Level::addMetaData( const std::string& key, const std::string& value )
{
    if( m_MetaData.find( key ) != m_MetaData.end() )
        throw Exception( "[Level::addMetaData] meta data already exists" );
    m_MetaData[key] = value;
    std::cout << "added meta data: " << key << ":" << value << std::endl;
}

// --------------------------------------------------------------
const std::string& Level::getMetaData( const std::string& key )
{
    std::map<std::string, std::string>::iterator p = m_MetaData.find( key );
    if( p == m_MetaData.end() )
        throw Exception( "[Level::getMetaData] meta data not found" );
    return p->second;
}

// --------------------------------------------------------------
void Level::streamAllMetaData( std::ostream& stream )
{
    for( std::map<std::string, std::string>::iterator it = m_MetaData.begin(); it != m_MetaData.end(); ++it )
        stream << it->first << ": " << it->second << std::endl;
}

// --------------------------------------------------------------
void Level::addCommentData( const std::string& comment )
{
    m_Comments.push_back( comment );
    std::cout << "added comment data: " << comment << std::endl;
}

// --------------------------------------------------------------
void Level::streamAllCommentData( std::ostream& stream )
{
    for( std::vector<std::string>::iterator it = m_Comments.begin(); it != m_Comments.end(); ++it )
        stream << *it << std::endl;
}

// --------------------------------------------------------------
void Level::insertTile( const Sokoban::Uint32& x, const Sokoban::Uint32& y, const char& tile )
{

    // check if character is valid
    if( validTiles.find_first_of(tile) == std::string::npos )
        throw Exception( "[Level::insertTile] attempt to insert invalid character into level array" );

    // resize array if necessary
    while( x+1 > m_LevelArray.size() )
    {
        m_LevelArray.push_back( std::vector<char>(0) );
        m_LevelArray[m_LevelArray.size()-1].resize( m_LevelArray[0].size(), 32 );
    }
    if( y+1 > m_LevelArray[0].size() )
        for( size_t i = 0; i != m_LevelArray.size(); ++i )
            m_LevelArray[i].resize( y+1, 32 );

    // write tile
    m_LevelArray[x][y] = tile;

}

// --------------------------------------------------------------
void Level::insertTileLine( const Sokoban::Uint32& y, const std::string& tiles )
{
    for( size_t x = 0; x != tiles.size(); ++x )
        this->insertTile( x, y, tiles[x] );
}

// --------------------------------------------------------------
void Level::streamAllTileData( std::ostream& stream )
{
    for( size_t y = 0; y != m_LevelArray[0].size(); ++y )
    {
        for( size_t x = 0; x != m_LevelArray.size(); ++x )
            stream << m_LevelArray[x][y];
        stream << std::endl;
    }
}

} // namespace Sokoban
