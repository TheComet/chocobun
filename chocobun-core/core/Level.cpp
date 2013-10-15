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
// Level.cpp
// --------------------------------------------------------------

// --------------------------------------------------------------
// include files

#include <core/Level.hpp>
#include <core/LevelListener.hpp>
#include <core/Exception.hpp>
#include <sstream>

// TODO Issue #6 - add import support for alternate tiles (as seen in the following validTiles definition)
// TODO Issue #7 - convert alternate tiles to conventional tiles for internal use
const std::string Chocobun::Level::validTiles = "#@+$*. _pPbB";

namespace Chocobun {

// --------------------------------------------------------------
Level::Level( void ) :
    m_IsLevelValid( false ),
    m_UndoDataIndex( -1 ), // type is unsigned, but the wrap around is intended
    m_DoDispatch( true )
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
        throw Exception( std::string("[Level::addMetaData] Error: meta data \"") + key + "\" already exists" );
    m_MetaData[key] = value;
}

// --------------------------------------------------------------
const std::string& Level::getMetaData( const std::string& key )
{
    std::map<std::string, std::string>::iterator p = m_MetaData.find( key );
    if( p == m_MetaData.end() )
        throw Exception( std::string("[Level::getMetaData] Error: meta data \"") + key + "\" not found" );
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
            return;
        }
    }
#ifdef _DEBUG
    std::cout << std::string("[Level::removeHeaderData] Warning: Header data \"") + header + "\" does not exist" << std::endl;
#endif
}

// --------------------------------------------------------------
void Level::streamAllHeaderData( std::ostream& stream )
{
    for( std::vector<std::string>::iterator it = m_HeaderData.begin(); it != m_HeaderData.end(); ++it )
        stream << *it << std::endl;
}

// --------------------------------------------------------------
void Level::insertTile( const std::size_t& x, const std::size_t& y, const char& tile )
{

    // check if character is valid
    if( validTiles.find_first_of(tile) == std::string::npos )
        throw Exception( std::string("[Level::insertTile] Error: attempt to insert invalid character \"") + tile + "\" into level array" );

    // resize array if necessary
    while( x+1 > m_LevelArray.size() )
    {
        m_LevelArray.push_back( std::vector<char>(0) );
        m_LevelArray[m_LevelArray.size()-1].resize( m_LevelArray[0].size(), 32 );
    }
    if( y+1 > m_LevelArray[0].size() )
        for( std::size_t i = 0; i != m_LevelArray.size(); ++i )
            m_LevelArray[i].resize( y+1, 32 );

    // write tile
    this->setTile( x, y, tile );

}

// --------------------------------------------------------------
void Level::insertTileLine( const std::size_t& y, const std::string& tiles )
{
    for( std::size_t x = 0; x != tiles.size(); ++x )
        this->insertTile( x, y, tiles[x] );
}

// --------------------------------------------------------------
void Level::streamAllTileData( std::ostream& stream, bool newLine )
{
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
}

// --------------------------------------------------------------
// TODO Issue #8 - It's cleaner to keep a copy of the initial tile data. Implement that instead of fast-forwarding and fast-backing
void Level::streamInitialTileData( std::ostream& stream, bool newLine )
{

    // disable listeners, as these tile updates are for internal purposes only
    bool tempDoDispatch = m_DoDispatch;
    this->doDispatch( false );

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

    // restore dispatch settings
    this->doDispatch( tempDoDispatch );
}

// --------------------------------------------------------------
// TODO Issue #9 - consider returning this as a reference again (instead of copying)
void Level::getTileData( std::vector< std::vector<char> >& vvs ) const
{
    vvs = m_LevelArray;
}

// --------------------------------------------------------------
char Level::getTile( std::size_t x, std::size_t y ) const
{
    if( x >= m_LevelArray.size() ){ std::stringstream ss;  ss << "[Level::getTile] X-coordinate out of bounds: " << x; throw Exception( ss.str() ); }
    if( y >= m_LevelArray[0].size() ){ std::stringstream ss; ss << "[Level::getTile] Y-coordinate out of bounds: " << y; throw Exception( ss.str() ); }
    return m_LevelArray[x][y];
}

// --------------------------------------------------------------
void Level::setTile( const std::size_t& x, const std::size_t& y, const char& tile )
{
    if( x >= m_LevelArray.size() ) { std::stringstream ss; ss << "[Level::setTile] X-coordinate out of bounds: " << x; throw Exception( ss.str() ); }
    if( y >= m_LevelArray[0].size() ) { std::stringstream ss; ss << "[Level::setTile] Y-coordinate out of bounds: " << y; throw Exception( ss.str() ); }
    if( validTiles.find( tile ) == std::string::npos ) throw Exception( std::string("[Level::setTile] attempt to set tile to invalid character: \"") + tile + "\"" );
    m_LevelArray[x][y] = tile;
    this->dispatchSetTile( x, y, tile );
}

// --------------------------------------------------------------
// TODO Does this actually return 0 if the tile array is empty?
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
            return;
        }
    }
#ifdef _DEBUG
    std::cout << std::string("[Level::removeLevelNote] Warning: note \"") + note + "\" was not found" << std::endl;
#endif
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
const std::string& Level::getLevelName( void ) const
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
    if( undoData.size() == 0 )
        throw Exception( std::string("[Level::importUndoData] Undo data string is empty") );

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
        // TODO Issue #10 - Use static const std::string for validation
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
            default:
                throw Exception( std::string("[Level::importUndoData] Invalid character found in undo data string: \"") + undoData + "\". Import failed." );
                break;
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
// TODO Issue #8 - Cleaner to copy initial tile data into array, and dispatch all tiles
void Level::reset( void )
{
    while( this->undo() );
    m_UndoData.clear();
    m_UndoDataIndex = -1;
}

// --------------------------------------------------------------
void Level::validateLevel( void )
{

    // does another check need to be done?
    if( m_IsLevelValid ) return;

    // make sure there's only one player
    // this also sets the internal positions of the player
    bool playerFound = false;
    for( std::size_t x = 0; x != m_LevelArray.size(); ++x )
    {
        for( std::size_t y = 0; y != m_LevelArray[0].size(); ++y )
        {
            if( m_LevelArray[x][y] == '@' || m_LevelArray[x][y] == '+' )
            {
                if( playerFound )
                {
                    throw Exception( "[Level::validateLevel] Error: More than one player was found on this level." );
                }else
                {
                    m_PlayerX = x;
                    m_PlayerY = y;
                    playerFound = true;
                }

            }
        }
    }
    if( !playerFound ) throw Exception( "[Level::validateLevel] Error: No player was found on this level." );

    // fast-forward player according to undo/redo data
    if( this->undoDataExists() )
        for( std::size_t pos = 0; pos != m_UndoDataIndex+1; ++pos )
            this->movePlayer( m_UndoData.at(pos), false );

    // arriving here means the level is valid
    m_IsLevelValid = true;
}

// --------------------------------------------------------------
void Level::moveUp( void )
{
    this->movePlayer( 'u' );
}

// --------------------------------------------------------------
void Level::moveDown( void )
{
    this->movePlayer( 'd' );
}

// --------------------------------------------------------------
void Level::moveLeft( void )
{
    this->movePlayer( 'l' );
}

// --------------------------------------------------------------
void Level::moveRight( void )
{
    this->movePlayer( 'r' );
}

// --------------------------------------------------------------
void Level::movePlayer( char direction, bool updateUndoData )
{

    if( !m_IsLevelValid )
    {
#ifdef _DEBUG
        std::cout << "[Level::movePlayer] Warning: attempt to move on an invalid level" << std::endl;
#endif
        return;
    }

    bool isPushingBox = false;

    // convert to lower case
    if( direction == 'U' || direction == 'D' || direction == 'L' || direction == 'R' ) direction += 32;

    // calculate new positions of player
    std::size_t newX = m_PlayerX, newY = m_PlayerY;
    if( direction == 'u' ) --newY;
    if( direction == 'd' ) ++newY;
    if( direction == 'l' ) --newX;
    if( direction == 'r' ) ++newX;

    // calculate next step the player would take if traveling linearly
    std::size_t nextX = newX + (newX-m_PlayerX);
    std::size_t nextY = newY + (newY-m_PlayerY);

    // can't move if there is a wall
    if( m_LevelArray[newX][newY] == '#' ) return;

    // can't move if box is against a wall or another box
    if( m_LevelArray[newX][newY] == '$' || m_LevelArray[newX][newY] == '*' )
    {
        if( m_LevelArray[nextX][nextY] == '#' ||
            m_LevelArray[nextX][nextY] == '$' ||
            m_LevelArray[nextX][nextY] == '*' )
            return;
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
            this->setTile( nextX, nextY, '*' );   // target is goal, place box on goal
        else
            this->setTile( nextX, nextY, '$' );     // target is floor, place box on floor
        this->dispatchMoveTile( newX, newY, nextX, nextY );
    }

    // move player
    if( m_LevelArray[newX][newY] == ' ' )
        this->setTile( newX, newY, '@' );     // target is floor, place player on floor
    else
        this->setTile( newX, newY, '+' );     // target is goal, place player on goal
    if( m_LevelArray[m_PlayerX][m_PlayerY] == '@')
        this->setTile( m_PlayerX, m_PlayerY, ' ' );
    else
        this->setTile( m_PlayerX, m_PlayerY, '.' );
    this->dispatchMoveTile( m_PlayerX, m_PlayerY, newX, newY );
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
    std::size_t oldX = m_PlayerX, oldY = m_PlayerY;
    if( move == 'u' ) ++oldY;
    if( move == 'd' ) --oldY;
    if( move == 'l' ) ++oldX;
    if( move == 'r' ) --oldX;

    // calculate previous step player would have taken if he were traveling linearly
    std::size_t previousX = m_PlayerX + (m_PlayerX-oldX);
    std::size_t previousY = m_PlayerY + (m_PlayerY-oldY);

    // revert back player position
    if( m_LevelArray[m_PlayerX][m_PlayerY] == '@' )
        this->setTile( m_PlayerX, m_PlayerY, ' ' );
    else
        this->setTile( m_PlayerX, m_PlayerY, '.' );
    if( m_LevelArray[oldX][oldY] == ' ' )
        this->setTile( oldX, oldY, '@' );
    else
        this->setTile( oldX, oldY, '+' );
    this->dispatchMoveTile( m_PlayerX, m_PlayerY, oldX, oldY );

    // player was pushing a box
    if( boxPushed )
    {
        if( m_LevelArray[previousX][previousY] == '$' )
            this->setTile( previousX, previousY, ' ' );
        else
            this->setTile( previousX, previousY, '.' );
        if( m_LevelArray[m_PlayerX][m_PlayerY] == ' ')
            this->setTile( m_PlayerX, m_PlayerY, '$' );
        else
            this->setTile( m_PlayerX, m_PlayerY, '*' );
        this->dispatchMoveTile( previousX, previousY, m_PlayerX, m_PlayerY );
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

// --------------------------------------------------------------
void Level::addListener( LevelListener* listener )
{
    for( std::vector<LevelListener*>::iterator it = m_LevelListeners.begin(); it != m_LevelListeners.end(); ++it )
        if( (*it) == listener )
            throw Exception( "[Level::addListener] Error: Listener has already been registered" );
    m_LevelListeners.push_back( listener );
}

// --------------------------------------------------------------
void Level::removeListener( LevelListener* listener )
{
    for( std::vector<LevelListener*>::iterator it = m_LevelListeners.begin(); it != m_LevelListeners.end(); ++it )
    {
        if( (*it) == listener )
        {
            m_LevelListeners.erase( it );
            return;
        }
    }
    throw Exception( "[Level::removeListener] Error: Listener could not be removed, as it wasn't registered as a listener to begin with" );
}

// --------------------------------------------------------------
// TODO Issue #8 - remove this as soon as a copy of the initial tile data has been implemented,
// as it won't be required anymore after that
void Level::doDispatch( bool flag )
{
    m_DoDispatch = flag;
}

// --------------------------------------------------------------
void Level::dispatchSetTile( const std::size_t& x, const std::size_t& y, const char& tile )
{
    if( !m_DoDispatch ) return;
    for( std::vector<LevelListener*>::iterator it = m_LevelListeners.begin(); it != m_LevelListeners.end(); ++it )
        (*it)->onSetTile( x, y, tile );
}

// --------------------------------------------------------------
void Level::dispatchMoveTile( const std::size_t& oldX, const std::size_t& oldY, const std::size_t& newX, const std::size_t& newY )
{
    if( !m_DoDispatch ) return;
    for( std::vector<LevelListener*>::iterator it = m_LevelListeners.begin(); it != m_LevelListeners.end(); ++it )
        (*it)->onMoveTile( oldX, oldY, newX, newY );
    std::cout << "move tile dispatched" << std::endl;
}

} // namespace Chocobun
