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
// Level
// --------------------------------------------------------------

// --------------------------------------------------------------
// include files

#include <core/Level.hpp>
#include <core/Exception.hpp>

const std::string Chocobun::Level::validTiles = "#@+$*. _pPbB";

namespace Chocobun {

// --------------------------------------------------------------
Level::Level( void ) :
    m_IsLevelValid( false ),
    m_UndoDataIndex( -1 ) // type is unsigned, but the wrap around is intended
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
void Level::insertTile( const Chocobun::Uint32& x, const Chocobun::Uint32& y, const char& tile )
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
void Level::insertTileLine( const Chocobun::Uint32& y, const std::string& tiles )
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
void Level::streamInitialTileData( std::ostream& stream, bool newLine )
{

    // save progress temporarily and reset to initial state
    std::size_t undoDataIndex = m_UndoDataIndex;
    if( m_IsLevelValid )
    {
        while( this->undo() );
    }

    // stream data
    for( std::size_t y = 0; y != m_LevelArray[0].size(); ++y )
    {
        for( std::size_t x = 0; x != m_LevelArray.size(); ++x )
            stream << m_LevelArray[x][y];
        if( newLine )
            stream << std::endl;
        else
            stream << "|";
    }
    if( !newLine ) stream << std::endl;

    // fast forward again to restore last state
    m_UndoDataIndex = undoDataIndex;
    if( m_IsLevelValid )
		if( undoDataIndex != -1 )
			for( std::size_t pos = 0; pos != m_UndoDataIndex; ++pos )
				this->movePlayer( m_UndoData.at(pos), false );

}

// --------------------------------------------------------------
const std::vector< std::vector<char> >& Level::getTileData( void ) const
{
    return m_LevelArray;
}

// --------------------------------------------------------------
char Level::getTile( std::size_t x, std::size_t y ) const
{
    if( x < 1 || x > m_LevelArray.size() ) return '\0';
    if( y < 1 || y > m_LevelArray[0].size() ) return '\0';
    return m_LevelArray[x-1][y-1];
}

// --------------------------------------------------------------
std::size_t Level::getSizeX( void ) const
{
    return m_LevelArray.size();
}

// --------------------------------------------------------------
std::size_t Level::getSizeY( void ) const
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
std::string Level::exportUndoData( void )
{
	std::string undoData( m_UndoData.begin(), m_UndoData.end() );
	if( this->undoDataExists() || this->redoDataExists() ) undoData.insert( m_UndoDataIndex+1, "*" );
	return undoData;
}

// --------------------------------------------------------------
void Level::importUndoData( const std::string& undoData )
{
	if( undoData.size() == 0 ) return;
	std::vector<char> tmp( undoData.begin(), undoData.end() );
	std::size_t pos = 0;
	for( std::vector<char>::iterator it = tmp.begin(); it != tmp.end(); ++it )
	{
		if( *it == '*' )
		{
			tmp.erase( it );
			break;
		}
		++pos;

		// validate characters
		switch( *it )
		{
			case 'u':break;
			case 'd':break;
			case 'l':break;
			case 'r':break;
			case 'U':break;
			case 'D':break;
			case 'L':break;
			case 'R':break;
			default: return; break;
		}
	}

	// set level state
	this->reset();
	m_UndoData = tmp;
	m_UndoDataIndex = pos-1;
	if( m_IsLevelValid )
		if( this->undoDataExists() )
			for( pos = 0; pos != m_UndoDataIndex; ++pos )
				this->movePlayer( m_UndoData.at(pos), false );

}

// --------------------------------------------------------------
void Level::reset( void )
{
	while( this->undo() );
	m_UndoData.clear();
	m_UndoDataIndex = -1;
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
            if( m_LevelArray[x][y] == '@' || m_LevelArray[x][y] == '+' )
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
	if( !playerFound ) return false;

	// fast-forward player according to undo/redo data
	if( this->undoDataExists() )
		for( std::size_t pos = 0; pos != m_UndoDataIndex+1; ++pos )
			this->movePlayer( m_UndoData.at(pos), false );

    // arriving here means the level is valid
    m_IsLevelValid = true;
    return true;
}

// --------------------------------------------------------------
void Level::moveUp( void )
{
    if( !m_IsLevelValid ) return;
    if( !this->movePlayer( 'u' ) ) return;
}

// --------------------------------------------------------------
void Level::moveDown( void )
{
    if( !m_IsLevelValid ) return;
    if( !this->movePlayer( 'd' ) ) return;
}

// --------------------------------------------------------------
void Level::moveLeft( void )
{
    if( !m_IsLevelValid ) return;
    if( !this->movePlayer( 'l' ) ) return;
}

// --------------------------------------------------------------
void Level::moveRight( void )
{
    if( !m_IsLevelValid ) return;
    if( !this->movePlayer( 'r' ) ) return;
}

// --------------------------------------------------------------
bool Level::movePlayer( char direction, bool updateUndoData )
{

    bool isPushingBox = false;

	// convert to lower case
	if( direction == 'U' || direction == 'D' || direction == 'L' || direction == 'R' ) direction += 32;

    // calculate new positions of player
    Uint32 newX = m_PlayerX, newY = m_PlayerY;
    if( direction == 'u' ) --newY;
    if( direction == 'd' ) ++newY;
    if( direction == 'l' ) --newX;
    if( direction == 'r' ) ++newX;

    // calculate next step the player would take if traveling linearly
    Uint32 nextX = newX + (newX-m_PlayerX);
    Uint32 nextY = newY + (newY-m_PlayerY);

    // can't move if there is a wall
    if( m_LevelArray[newX][newY] == '#' ) return false;

    // can't move if box is against a wall or another box
    if( m_LevelArray[newX][newY] == '$' || m_LevelArray[newX][newY] == '*' )
    {
        if( m_LevelArray[nextX][nextY] == '#' ||
            m_LevelArray[nextX][nextY] == '$' ||
            m_LevelArray[nextX][nextY] == '*' )
            return false;
        isPushingBox = true;
    }

    // move box (if any)
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

    // move player
    if( m_LevelArray[newX][newY] == ' ' )
        m_LevelArray[newX][newY] = '@';     // target is floor, place player on floor
    else
        m_LevelArray[newX][newY] = '+';     // target is goal, place player on goal
    if( m_LevelArray[m_PlayerX][m_PlayerY] == '@')
        m_LevelArray[m_PlayerX][m_PlayerY] = ' ';
    else
        m_LevelArray[m_PlayerX][m_PlayerY] = '.';
	m_PlayerX = newX;
	m_PlayerY = newY;

    // generate undo data
	if( updateUndoData )
	{
		if( isPushingBox ) direction -= 32; // convert to upper case for pushing boxes
		if( this->undoDataExists() )
			while( m_UndoData.size()-1 != m_UndoDataIndex )
				m_UndoData.pop_back();
		m_UndoData.push_back( direction );
		++m_UndoDataIndex;
	}

    return true;
}

// --------------------------------------------------------------
bool Level::undo( void )
{
    if( !m_IsLevelValid ) return false;
	if( !this->undoDataExists() ) return false;

    // get undo move
    char move = m_UndoData.at( m_UndoDataIndex );
    --m_UndoDataIndex;

    // determine if a box was pushed and convert to lower case
    bool boxPushed = false;
    if( move == 'U' || move == 'D' || move == 'L' || move == 'R' )
    {
        boxPushed = true;
        move += 32; // convert to lower case
    }

    // calculate old positions
    Uint32 oldX = m_PlayerX, oldY = m_PlayerY;
    if( move == 'u' ) ++oldY;
    if( move == 'd' ) --oldY;
    if( move == 'l' ) ++oldX;
    if( move == 'r' ) --oldX;

    // calculate previous step player would have taken if he were traveling linearly
    Uint32 previousX = m_PlayerX + (m_PlayerX-oldX);
    Uint32 previousY = m_PlayerY + (m_PlayerY-oldY);

    // revert back player position
    if( m_LevelArray[m_PlayerX][m_PlayerY] == '@' )
        m_LevelArray[m_PlayerX][m_PlayerY] = ' ';
    else
        m_LevelArray[m_PlayerX][m_PlayerY] = '.';
    if( m_LevelArray[oldX][oldY] == ' ' )
        m_LevelArray[oldX][oldY] = '@';
    else
        m_LevelArray[oldX][oldY] = '+';

    // player was pushing a box
    if( boxPushed )
    {
        if( m_LevelArray[previousX][previousY] == '$' )
            m_LevelArray[previousX][previousY] = ' ';
        else
            m_LevelArray[previousX][previousY] = '.';
        if( m_LevelArray[m_PlayerX][m_PlayerY] == ' ')
            m_LevelArray[m_PlayerX][m_PlayerY] = '$';
        else
            m_LevelArray[m_PlayerX][m_PlayerY] = '*';
    }
	m_PlayerX = oldX;
	m_PlayerY = oldY;

	return true;
}

// --------------------------------------------------------------
bool Level::redo( void )
{
    if( !m_IsLevelValid ) return false;
    if( !this->redoDataExists() ) return false;
	char move = m_UndoData.at(m_UndoDataIndex+1);
    this->movePlayer( move, false );
	++m_UndoDataIndex;
	return true;
}

// --------------------------------------------------------------
bool Level::undoDataExists( void )
{
	return ( m_UndoDataIndex!=-1 );
}

// --------------------------------------------------------------
bool Level::redoDataExists( void )
{
    return ( m_UndoDataIndex+1 < m_UndoData.size() );
}

} // namespace Chocobun
