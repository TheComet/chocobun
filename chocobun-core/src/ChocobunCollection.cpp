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
// Collection.cpp
// --------------------------------------------------------------

// --------------------------------------------------------------
// include files

#include <ChocobunCollection.hpp>
#include <ChocobunCollectionParser.hpp>
#include <ChocobunException.hpp>
#include <ChocobunLevel.hpp>

#include <iostream>
#include <sstream>

namespace Chocobun {

// --------------------------------------------------------------
Collection::Collection( void ) :
    m_ActiveLevel( -1 )
{
}

// --------------------------------------------------------------
Collection::Collection( const Collection& that ) :
    m_ActiveLevel( -1 )
{
    *this = that;
}

// --------------------------------------------------------------
Collection::~Collection( void )
{
    //this->unload();
}
/*
// --------------------------------------------------------------
void Collection::load( const std::string& fileName )
{
#ifdef _DEBUG
    std::cout << "Loading collection" << std::endl;
#endif

    if( m_IsLoaded )
    {
#ifdef _DEBUG
        std::cout << "[Collection::load] Warning: Collection is already initialised" << std::endl;
#endif
        return;
    }

    // load and parse levels
    m_FileName = fileName;
    CollectionParser cp;
    cp.parse( m_FileName, *this );

    m_IsLoaded = true;
}

// --------------------------------------------------------------
void Collection::unload( void )
{
#ifdef _DEBUG
    std::cout << "Unloading collection" << std::endl;
#endif

    if( !m_IsLoaded )
    {
#ifdef _DEBUG
        std::cout << "[Collection::unload] Warning: Collection is not loaded" << std::endl;
#endif
        return;
    }

    // destroy levels
    for( std::vector<Level*>::iterator it = m_Levels.begin(); it != m_Levels.end(); ++it )
        delete *it;
    m_Levels.clear();
    m_ActiveLevel = -1;

    m_IsLoaded = false;
}

// --------------------------------------------------------------
void Collection::save( const std::string& fileFormat )
{
    CollectionParser cp;
    cp.setFileFormat( fileFormat );
    cp.save( m_FileName, *this, m_EnableCompression );
}*/

// --------------------------------------------------------------
void Collection::setCollectionName( const std::string& name )
{
    m_CollectionName = name;
}

// --------------------------------------------------------------
const std::string& Collection::getCollectionName( void ) const
{
	return m_CollectionName;
}
/*
// --------------------------------------------------------------
void Collection::enableCompression( void )
{
    m_EnableCompression = true;
}

// --------------------------------------------------------------
void Collection::disableCompression( void )
{
    m_EnableCompression = false;
}

// --------------------------------------------------------------
bool Collection::isCompressionEnabled( void ) const
{
    return m_EnableCompression;
}
*/
// --------------------------------------------------------------
Level* Collection::addLevel( void )
{
    m_Levels.push_back( new Level() );
    return m_Levels.front();
}

// --------------------------------------------------------------
void Collection::removeLevel( Level* lvl )
{
    for( std::vector<Level*>::iterator it = m_Levels.begin(); it != m_Levels.end(); ++it )
        if( *it == lvl )
        {

            // reset active level if it is being removed
            if( m_Levels[m_ActiveLevel] == *it )
                m_ActiveLevel = -1;

            // remove level
            delete *it;
            it = m_Levels.erase( it );

            return;
        }
    throw Exception( "[Collection::removeLevel] Error: Level not registered to this collection." );
}

// --------------------------------------------------------------
void Collection::removeLevel( const std::string& levelName )
{
    for( std::vector<Level*>::iterator it = m_Levels.begin(); it != m_Levels.end(); ++it )
        if( (*it)->getLevelName() == levelName )
        {

            // reset active level if it is being removed
            if( m_Levels[m_ActiveLevel] == *it )
                m_ActiveLevel = -1;

            // remove level
            delete *it;
            it = m_Levels.erase( it );

            return;
        }
    throw Exception( "[Collection::removeLevel] Error: Level not registered to this collection: " + levelName );
}

// --------------------------------------------------------------
void Collection::generateLevelName( std::string& name )
{
    std::stringstream ss;
    std::vector<Level*>::iterator it;
    if( name.size() == 0 )
    {
        Uint32 i = 1;
        do{
            ss.clear();
            ss.str("");
            ss << "Level #";
            ss << i;
            ++i;
            for( it = m_Levels.begin(); it != m_Levels.end(); ++it )
                if( (*it)->getLevelName().compare(ss.str()) == 0 )
                    break;
        }while( it != m_Levels.end() );
        name = ss.str();
        std::cout << "generated level name " << name << std::endl;
    }
}

// --------------------------------------------------------------
Level* Collection::getLevelPtr( const std::string& levelName ) const
{
    for( std::vector<Level*>::const_iterator it = m_Levels.begin(); it != m_Levels.end(); ++it )
    {
        if( (*it)->getLevelName() == levelName )
            return *it;
    }
    throw Exception( "[Collection::getLevelPtr] Error: Level not registered to this collection: " + levelName );
}

// --------------------------------------------------------------
Level* Collection::getLevelPtr( const std::size_t& ID ) const
{
    if( ID >= m_Levels.size() )
        throw Exception( "[Collection::getLevelPtr] Error: Level ID out of bounds: " + ID );
    return m_Levels[ ID ];
}

// --------------------------------------------------------------
Level& Collection::getLevel( const std::string& levelName ) const
{
    return *this->getLevelPtr( levelName );
}

// --------------------------------------------------------------
Level& Collection::getLevel( const std::size_t& ID ) const
{
    return *this->getLevelPtr( ID );
}

// --------------------------------------------------------------
std::vector<std::string> Collection::getLevelNames( void ) const
{

    std::vector<std::string> vs;
    for( std::vector<Level*>::const_iterator it = m_Levels.begin();
         it != m_Levels.end(); ++it )
        vs.push_back( (*it)->getLevelName() );
    return vs;
}

// --------------------------------------------------------------
void Collection::streamLevelNames( std::ostream& stream ) const
{
    for( std::vector<Level*>::const_iterator it = m_Levels.begin();
         it != m_Levels.end(); ++it )
        stream << (*it)->getLevelName() << std::endl;
}

// --------------------------------------------------------------
void Collection::selectFirstLevel( void )
{
    if( m_Levels.size() == 0 ) return;
    this->setActiveLevel( m_Levels.front()->getLevelName() );
}

// --------------------------------------------------------------
void Collection::selectLastLevel( void )
{
    if( m_Levels.size() == 0 ) return;
    this->setActiveLevel( m_Levels.back()->getLevelName() );
}

// --------------------------------------------------------------
bool Collection::selectNextLevel( void )
{
    if( m_ActiveLevel == -1 || m_ActiveLevel+1 == m_Levels.size() ) return false;
    ++m_ActiveLevel;
    this->setActiveLevel( m_Levels[m_ActiveLevel]->getLevelName() );
    return true;
}

// --------------------------------------------------------------
bool Collection::selectPreviousLevel( void )
{
    if( m_ActiveLevel == -1 || m_ActiveLevel-1 == 0 ) return false;
    --m_ActiveLevel;
    this->setActiveLevel( m_Levels[m_ActiveLevel]->getLevelName() );
    return true;
}

// --------------------------------------------------------------
void Collection::setActiveLevel( const std::string& levelName )
{

    // get new active level index
    std::size_t newActiveLevel = -1;
    for( std::size_t i = 0; i != m_Levels.size(); ++i )
    {
        if( m_Levels[i]->getLevelName().compare( levelName ) == 0 )
        {
            newActiveLevel = i;
            break;
        }
    }

    // none found
    if( newActiveLevel == -1 )
        throw Exception( std::string("[Collection::setActiveLevel] Error: Level name \"") + levelName + "\" was not found in loaded collection" );

    // prepare the level to play on
    m_Levels[newActiveLevel]->validateLevel();
    m_Levels[newActiveLevel]->reset();
    m_Levels[newActiveLevel]->applyUndoData();

    // set the new level
    m_ActiveLevel = newActiveLevel;

}

// --------------------------------------------------------------
bool Collection::hasActiveLevel( void )
{
    return ( m_ActiveLevel != -1 );
}
/*
// --------------------------------------------------------------
Collection::level_iterator Collection::level_begin( void )
{
    return m_Levels.begin();
}

// --------------------------------------------------------------
Collection::level_iterator Collection::level_end( void )
{
    return m_Levels.end();
}

// --------------------------------------------------------------
const Collection::const_level_iterator Collection::level_begin( void ) const
{
    return m_Levels.begin();
}

// --------------------------------------------------------------
const Collection::const_level_iterator Collection::level_end( void ) const
{
    return m_Levels.end();
}

// --------------------------------------------------------------
void Collection::getTileData( Array2D<char>& tiles ) const
{
    if( m_ActiveLevel == -1 )
    {
#ifdef _DEBUG
        std::cout << "[Collection::getTileData] Error: Attempt to get tile data without first setting an active level" << std::endl;
#endif
        return;
    }
    m_Levels[m_ActiveLevel]->getTileData( tiles );
}

// --------------------------------------------------------------
void Collection::streamTileData( std::ostream& stream )
{
    if( m_ActiveLevel == -1 )
    {
#ifdef _DEBUG
        std::cout << "[Collection::streamTiledata] Warning: Attempt to stream tile data without first setting an active level" << std::endl;
#endif
        return;
    }
    m_Levels[m_ActiveLevel]->streamAllTileData( stream );
}

// --------------------------------------------------------------
char Collection::getTile( const Uint32 x, const Uint32 y )
{
    if( m_ActiveLevel == -1 )
        throw Exception( "[Collection::getTile] Error: Attempt to get tile without first setting an active level" );
    return m_Levels[m_ActiveLevel]->getTile( x, y );
}

// --------------------------------------------------------------
void Collection::setTile( const Uint32 x, const Uint32 y, const char tile )
{
   if( m_ActiveLevel == -1 )
    {
#ifdef _DEBUG
        std::cout << "[Collection::setTile] Warning: Attempt to set a tile without first setting an active level" << std::endl;
#endif
        return;
    }
    m_Levels[m_ActiveLevel]->setInitialTile( x, y, tile );
}

// --------------------------------------------------------------
Uint32 Collection::getSizeX( void ) const
{
    if( m_ActiveLevel == -1 )
        throw Exception( "[Collection::getSizeX] Error: No active level set" );
    return m_Levels[m_ActiveLevel]->getSizeX();
}

// --------------------------------------------------------------
Uint32 Collection::getSizeY( void ) const
{
    if( m_ActiveLevel == -1 )
        throw Exception( "[Collection::getSizeY] Error: No active level set" );
    return m_Levels[m_ActiveLevel]->getSizeY();
}

// --------------------------------------------------------------
Uint32 Collection::getMaxSizeX( void )
{
    Uint32 max;
    for( std::vector<Level*>::iterator it = m_Levels.begin(); it != m_Levels.end(); ++it )
        if( (*it)->getSizeX() > max ) max = (*it)->getSizeX();
    return max;
}

// --------------------------------------------------------------
Uint32 Collection::getMaxSizeY( void )
{
    Uint32 max;
    for( std::vector<Level*>::iterator it = m_Levels.begin(); it != m_Levels.end(); ++it )
        if( (*it)->getSizeY() > max ) max = (*it)->getSizeY();
    return max;
}

// --------------------------------------------------------------
void Collection::addLevelListener( LevelListener* listener )
{
    for( std::vector<LevelListener*>::iterator it = m_LevelListeners.begin(); it != m_LevelListeners.end(); ++it )
        if( (*it) == listener )
            throw Exception( "[Collection::addLevelListener] Error: Listener has already been registered" );
    m_LevelListeners.push_back( listener );
}

// --------------------------------------------------------------
void Collection::removeLevelListener( LevelListener* listener )
{
    for( std::vector<LevelListener*>::iterator it = m_LevelListeners.begin(); it != m_LevelListeners.end(); ++it )
    {
        if( (*it) == listener )
        {
            m_LevelListeners.erase( it );
            return;
        }
    }
    throw Exception( "[Collection::removeLevelListener] Error: Listener could not be removed, as it wasn't registered as a listener to begin with" );
}

// --------------------------------------------------------------
void Collection::moveUp( void )
{
    if( m_ActiveLevel == -1 )
    {
#ifdef _DEBUG
        std::cout << "[Collection::moveUp] Warning: No active level set" << std::endl;
#endif
        return;
    }
    m_Levels[m_ActiveLevel]->moveUp();
}

// --------------------------------------------------------------
void Collection::moveDown( void )
{
    if( m_ActiveLevel == -1 )
    {
#ifdef _DEBUG
        std::cout << "[Collection::moveDown] Warning: No active level set" << std::endl;
#endif
        return;
    }
    m_Levels[m_ActiveLevel]->moveDown();
}

// --------------------------------------------------------------
void Collection::moveLeft( void )
{
    if( m_ActiveLevel == -1 )
    {
#ifdef _DEBUG
        std::cout << "[Collection::moveLeft] Warning: No active level set" << std::endl;
#endif
        return;
    }
    m_Levels[m_ActiveLevel]->moveLeft();
}

// --------------------------------------------------------------
void Collection::moveRight( void )
{
    if( m_ActiveLevel == -1 )
    {
#ifdef _DEBUG
        std::cout << "[Collection::moveRight] Warning: No active level set" << std::endl;
#endif
        return;
    }
    m_Levels[m_ActiveLevel]->moveRight();
}

// --------------------------------------------------------------
void Collection::undo( void )
{
    if( m_ActiveLevel == -1 )
    {
#ifdef _DEBUG
        std::cout << "[Collection::undo] Warning: No active level set" << std::endl;
#endif
        return;
    }
    m_Levels[m_ActiveLevel]->undo();
}

// --------------------------------------------------------------
void Collection::redo( void )
{
    if( m_ActiveLevel == -1 )
    {
#ifdef _DEBUG
        std::cout << "[Collection::redo] Warning: No active level set" << std::endl;
#endif
        return;
    }
    m_Levels[m_ActiveLevel]->redo();
}

// --------------------------------------------------------------
void Collection::reset( void )
{
    if( m_ActiveLevel == -1 )
    {
#ifdef _DEBUG
        std::cout << "[Collection::reset] Warning: No active level set" << std::endl;
#endif
        return;
    }
    m_Levels[m_ActiveLevel]->reset();
    m_Levels[m_ActiveLevel]->clearUndoData();
}

// --------------------------------------------------------------
void Collection::onSetTile( const std::size_t& x, const std::size_t& y, const char& tile )
{
    for( std::vector<LevelListener*>::iterator it = m_LevelListeners.begin(); it != m_LevelListeners.end(); ++it )
        (*it)->onSetTile( x, y, tile );
}

// --------------------------------------------------------------
void Collection::onMoveTile( const std::size_t& oldX, const std::size_t& oldY, const std::size_t& newX, const std::size_t& newY )
{
    for( std::vector<LevelListener*>::iterator it = m_LevelListeners.begin(); it != m_LevelListeners.end(); ++it )
        (*it)->onMoveTile( oldX, oldY, newX, newY );
}
*/
// --------------------------------------------------------------
Collection& Collection::operator=( const Collection& that )
{
    if( this == &that ) return *this;

    // shallow copies
    this->m_CollectionName = that.m_CollectionName;
    this->m_ActiveLevel = that.m_ActiveLevel;

    // re-allocate memory for level objects to match the size of "that"
    for( std::vector<Level*>::iterator it = m_Levels.begin(); it != m_Levels.end(); ++it )
        delete *it;
    m_Levels.clear();
    for( std::vector<Level*>::const_iterator it = that.m_Levels.begin(); it != that.m_Levels.end(); ++it )
        m_Levels.push_back( new Level() );

    // deep copy level objects
    for( std::size_t i = 0; i != that.m_Levels.size(); ++i )
        *(m_Levels[i]) = *(that.m_Levels[i]);

    return *this;
}

} // namespace Chocobun
