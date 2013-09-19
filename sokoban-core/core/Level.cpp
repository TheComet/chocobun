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

const std::string Sokoban::Level::validTiles = "#@+$*. _pPbB";

namespace Sokoban {

// --------------------------------------------------------------
Level::Level( void ) :
    m_IsLevelValid( false )
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
void Level::addHeaderData( const std::string& header )
{
    m_HeaderData.push_back( header );
}

// --------------------------------------------------------------
void Level::removeHeaderData( const std::string& header )
{
    for( std::vector<std::string>::iterator it = m_HeaderData.begin(); it != m_HeaderData.end(); ++it )
    {
        if( it->compare( header ) == 0 )
        {
            m_HeaderData.erase( it );
            break;
        }
    }
}

// --------------------------------------------------------------
void Level::streamAllHeaderData( std::ostream& stream )
{
    for( std::vector<std::string>::iterator it = m_HeaderData.begin(); it != m_HeaderData.end(); ++it )
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
void Level::streamAllTileData( std::ostream& stream, bool newLine )
{
    for( size_t y = 0; y != m_LevelArray[0].size(); ++y )
    {
        for( size_t x = 0; x != m_LevelArray.size(); ++x )
            stream << m_LevelArray[x][y];
        if( newLine )
            stream << std::endl;
        else
            stream << "|";
    }
    if( !newLine ) stream << std::endl;
}

// --------------------------------------------------------------
const std::vector< std::vector<char> >& Level::getTileData( void ) const
{
    return m_LevelArray;
}

// --------------------------------------------------------------
char Level::getTile( Uint32 x, Uint32 y ) const
{
    if( x < 1 || x > m_LevelArray.size() ) return '\0';
    if( y < 1 || y > m_LevelArray[0].size() ) return '\0';
    return m_LevelArray[x-1][y-1];
}

// --------------------------------------------------------------
Uint32 Level::getSizeX( void ) const
{
    return m_LevelArray.size();
}

// --------------------------------------------------------------
Uint32 Level::getSizeY( void ) const
{
    return m_LevelArray[0].size();
}

// --------------------------------------------------------------
void Level::addLevelNote( const std::string& note )
{
    m_Notes.push_back( note );
}

// --------------------------------------------------------------
void Level::removeLevelNote( const std::string& note)
{
    for( std::vector<std::string>::iterator it = m_Notes.begin(); it != m_Notes.end(); ++it )
    {
        if( it->compare( note ) == 0 )
        {
            m_Notes.erase( it );
            break;
        }
    }
}

// --------------------------------------------------------------
void Level::streamAllNotes( std::ostream& stream )
{
    for( std::vector<std::string>::iterator it = m_Notes.begin(); it != m_Notes.end(); ++it )
        stream << *it << std::endl;
}

// --------------------------------------------------------------
void Level::setLevelName( const std::string& name )
{
    m_LevelName = name;
}

// --------------------------------------------------------------
std::string Level::getLevelName( void ) const
{
    return m_LevelName;
}

// --------------------------------------------------------------
bool Level::validateLevel( void )
{

    // does another check need to be done?
    if( m_IsLevelValid ) return true;

    // make sure there's only one player
    // this also sets the internal positions of the player
    bool playerFound = false;
    for( size_t x = 0; x != m_LevelArray.size(); ++x )
    {
        for( size_t y = 0; y != m_LevelArray[0].size(); ++y )
        {
            if( m_LevelArray[x][y] == '@' )
            {
                if( playerFound )
                {
                    return false;
                }else
                {
                    m_PlayerX = x;
                    m_PlayerY = y;
                    playerFound = true;
                }

            }
        }
    }

    // arriving here means the level is valid
    m_IsLevelValid = true;
    return true;
}

// --------------------------------------------------------------
void Level::moveUp( void )
{
    if( !m_IsLevelValid ) return;
    if( !this->movePlayer( m_PlayerX, m_PlayerY-1 ) ) return;
    --m_PlayerY;
}

// --------------------------------------------------------------
void Level::moveDown( void )
{
    if( !m_IsLevelValid ) return;
    if( !this->movePlayer( m_PlayerX, m_PlayerY+1 ) ) return;
    ++m_PlayerY;
}

// --------------------------------------------------------------
void Level::moveLeft( void )
{
    if( !m_IsLevelValid ) return;
    if( !this->movePlayer( m_PlayerX-1, m_PlayerY ) ) return;
    --m_PlayerX;
}

// --------------------------------------------------------------
void Level::moveRight( void )
{
    if( !m_IsLevelValid ) return;
    if( !this->movePlayer( m_PlayerX+1, m_PlayerY ) ) return;
    ++m_PlayerX;
}

// --------------------------------------------------------------
bool Level::movePlayer( const Uint32 newX, const Uint32 newY )
{

    bool isPushingBox = false;

    // calculate next step the player would take if traveling linearly
    Uint32 nextX = newX + (newX-m_PlayerX);
    Uint32 nextY = newY + (newY-m_PlayerY);

    // can't move up if there is a wall
    if( m_LevelArray[newX][newY] == '#' ) return false;

    // can't move up if box is against a wall or another box
    if( m_LevelArray[newX][newY] == '$' || m_LevelArray[newX][newY] == '*' )
    {
        if( m_LevelArray[nextX][nextY] == '#' ||
            m_LevelArray[nextX][nextY] == '$' ||
            m_LevelArray[nextX][nextY] == '*' )
            return false;
        isPushingBox = true;
    }

    // move box up (if any)
    if( isPushingBox )
    {
        if( m_LevelArray[newX][newY] == '$' )
            m_LevelArray[newX][newY] = ' ';   // box is on floor, expose floor
        else
            m_LevelArray[newX][newY] = '.';   // box is on goal, expose goal
        if( m_LevelArray[nextX][nextY] == '.' )
            m_LevelArray[nextX][nextY] = '*';   // target is goal, place box on goal
        else
            m_LevelArray[nextX][nextY] = '$';     // target is floor, place box on floor
    }

    // move player up
    if( m_LevelArray[newX][newY] == ' ' )
        m_LevelArray[newX][newY] = '@';     // target is floor, place player on floor
    else
        m_LevelArray[newX][newY] = '+';     // target is goal, place player on goal
    m_LevelArray[m_PlayerX][m_PlayerY] = ' ';

    return true;
}

// --------------------------------------------------------------
void Level::undo( void )
{
    if( !m_IsLevelValid ) return;
}

// --------------------------------------------------------------
void Level::redo( void )
{
    if( !m_IsLevelValid ) return;
}

} // namespace Sokoban
