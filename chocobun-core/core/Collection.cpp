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

#include <core/Collection.hpp>
#include <core/CollectionParser.hpp>
#include <core/Exception.hpp>
#include <core/Level.hpp>

#include <iostream>
#include <sstream>

namespace Chocobun {

// --------------------------------------------------------------
Collection::Collection( void ) :
    m_EnableCompression( false ),
    m_IsLoaded( false ),
    m_ActiveLevel( 0 ),
    m_FileFormat( CollectionParser::FORMAT_SOK )
{
}

// --------------------------------------------------------------
Collection::Collection( const Collection& that ) :
    m_ActiveLevel( 0 )
{
    *this = that;
}

// --------------------------------------------------------------
Collection::~Collection( void )
{
    this->unload();
}

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

    // export levels
    CollectionParser cp;
    cp.setFileFormat( m_FileFormat );
    cp.save( m_CollectionName, *this, m_EnableCompression );

    // destroy levels
    for( std::vector<Level*>::iterator it = m_Levels.begin(); it != m_Levels.end(); ++it )
        delete *it;
    m_Levels.clear();
    m_ActiveLevel = 0;

    m_IsLoaded = false;
}

// --------------------------------------------------------------
void Collection::setName( const std::string& name )
{
    m_CollectionName = name;
}

// --------------------------------------------------------------
const std::string& Collection::getName( void ) const
{
	return m_CollectionName;
}

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

// --------------------------------------------------------------
void Collection::setFileFormat( CollectionParser::FILE_FORMAT fileFormat )
{
    m_FileFormat = fileFormat;
}

// --------------------------------------------------------------
CollectionParser::FILE_FORMAT Collection::getFileFormat( void )
{
    return m_FileFormat;
}

// --------------------------------------------------------------
Level* Collection::addLevel( void )
{
    m_Levels.push_back( new Level() );
    return m_Levels.back();
}

// --------------------------------------------------------------
void Collection::removeLevel( Level* lvl )
{
    for( std::vector<Level*>::iterator it = m_Levels.begin(); it != m_Levels.end(); ++it )
    {
        if( *it == lvl )
        {
            delete *it;
            m_Levels.erase( it );
            return;
        }
    }
    throw Exception( "[Collection::removeLevel] Error: Level not registered to this collection." );
}

// --------------------------------------------------------------
void Collection::removeLevel( const std::string& levelName )
{
    for( std::vector<Level*>::iterator it = m_Levels.begin(); it != m_Levels.end(); ++it )
    {
        if( (*it)->getLevelName() == levelName )
        {
            delete *it;
            m_Levels.erase( it );
            return;
        }
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
Level* Collection::getLevelPtr( const std::string& levelName )
{
    for( std::vector<Level*>::iterator it = m_Levels.begin(); it != m_Levels.end(); ++it )
    {
        if( (*it)->getLevelName() == levelName )
            return *it;
    }
    throw Exception( "[Collection::getLevelPtr] Error: Level not registered to this collection: " + levelName );
}

// --------------------------------------------------------------
Level& Collection::getLevel( const std::string& levelName )
{
    return *this->getLevelPtr( levelName );
}

// --------------------------------------------------------------
void Collection::getLevelNames( std::vector<std::string>& vs )
{
#ifdef _DEBUG
    if( !m_IsLoaded )
        std::cout << "[Collection::getLevelNames] Warning: Levels haven't been\
 loaded yet (collection isn't initialised)" << std::endl;
#endif
    vs.clear();
    for( std::vector<Level*>::iterator it = m_Levels.begin();
         it != m_Levels.end(); ++it )
        vs.push_back( (*it)->getLevelName() );
}

// --------------------------------------------------------------
void Collection::streamLevelNames( std::ostream& stream )
{
#ifdef _DEBUG
    if( !m_IsLoaded )
        std::cout << "[Collection::streamLevelNames] Warning: Levels haven't \
been loaded yet (collection isn't initialised)" << std::endl;
#endif
    for( std::vector<Level*>::iterator it = m_Levels.begin();
         it != m_Levels.end(); ++it )
        stream << (*it)->getLevelName() << std::endl;
}

// --------------------------------------------------------------
void Collection::setActiveLevel( const std::string& levelName )
{
#ifdef _DEBUG
    if( !m_IsLoaded )
        std::cout << "[Collection::setActiveLevel] Warning: Levels haven't \
been loaded yet (collection isn't initialised)" << std::endl;
#endif

    // get new active level pointer
    Level* newActiveLevel = 0;
    for( std::vector<Level*>::iterator it = m_Levels.begin(); it != m_Levels.end(); ++it )
    {
        if( (*it)->getLevelName().compare( levelName ) == 0 )
        {
            newActiveLevel = (*it);
            break;
        }
    }

    // none found
    if( !newActiveLevel )
        throw Exception( std::string("[Collection::setActiveLevel] Error: Level name \"") + levelName + "\" was not found in loaded collection" );

    // prepare the level to play on
    newActiveLevel->validateLevel();
    newActiveLevel->reset();
    newActiveLevel->applyUndoData();

    // set the new level
    m_ActiveLevel = newActiveLevel;

}

// --------------------------------------------------------------
bool Collection::hasActiveLevel( void )
{
    if( m_ActiveLevel ) return true;
    return false;
}

// --------------------------------------------------------------
void Collection::getTileData( Array2D<char>& tiles ) const
{
    if( !m_ActiveLevel)
    {
#ifdef _DEBUG
        std::cout << "[Collection::getTileData] Error: Attempt to get tile data without first setting an active level" << std::endl;
#endif
        return;
    }
    m_ActiveLevel->getTileData( tiles );
}

// --------------------------------------------------------------
void Collection::streamTileData( std::ostream& stream )
{
    if( !m_ActiveLevel)
    {
#ifdef _DEBUG
        std::cout << "[Collection::streamTiledata] Warning: Attempt to stream tile data without first setting an active level" << std::endl;
#endif
        return;
    }
    m_ActiveLevel->streamAllTileData( stream );
}

// --------------------------------------------------------------
char Collection::getTile( const Uint32 x, const Uint32 y )
{
    if( !m_ActiveLevel )
        throw Exception( "[Collection::getTile] Error: Attempt to get tile without first setting an active level" );
    return m_ActiveLevel->getTile( x, y );
}

// --------------------------------------------------------------
void Collection::setTile( const Uint32 x, const Uint32 y, const char tile )
{
   if( !m_ActiveLevel )
    {
#ifdef _DEBUG
        std::cout << "[Collection::setTile] Warning: Attempt to set a tile without first setting an active level" << std::endl;
#endif
        return;
    }
    m_ActiveLevel->setInitialTile( x, y, tile );
}

// --------------------------------------------------------------
Uint32 Collection::getSizeX( void ) const
{
    if( !m_ActiveLevel )
        throw Exception( "[Collection::getSizeX] Error: No active level set" );
    return m_ActiveLevel->getSizeX();
}

// --------------------------------------------------------------
Uint32 Collection::getSizeY( void ) const
{
    if( !m_ActiveLevel )
        throw Exception( "[Collection::getSizeY] Error: No active level set" );
    return m_ActiveLevel->getSizeY();
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
    for( std::vector<Level*>::iterator it = m_Levels.begin(); it != m_Levels.end(); ++it )
        (*it)->addListener( listener );
}

// --------------------------------------------------------------
void Collection::removeLevelListener( LevelListener* listener )
{
    for( std::vector<LevelListener*>::iterator it = m_LevelListeners.begin(); it != m_LevelListeners.end(); ++it )
    {
        if( (*it) == listener )
        {
            for( std::vector<Level*>::iterator l_it = m_Levels.begin(); l_it != m_Levels.end(); ++l_it )
                (*l_it)->removeListener( listener );
            m_LevelListeners.erase( it );
            return;
        }
    }
    throw Exception( "[Collection::removeLevelListener] Error: Listener could not be removed, as it wasn't registered as a listener to begin with" );
}

// --------------------------------------------------------------
void Collection::moveUp( void )
{
    if( !m_ActiveLevel )
    {
#ifdef _DEBUG
        std::cout << "[Collection::moveUp] Warning: No active level set" << std::endl;
#endif
        return;
    }
    m_ActiveLevel->moveUp();
}

// --------------------------------------------------------------
void Collection::moveDown( void )
{
    if( !m_ActiveLevel )
    {
#ifdef _DEBUG
        std::cout << "[Collection::moveDown] Warning: No active level set" << std::endl;
#endif
        return;
    }
    m_ActiveLevel->moveDown();
}

// --------------------------------------------------------------
void Collection::moveLeft( void )
{
    if( !m_ActiveLevel )
    {
#ifdef _DEBUG
        std::cout << "[Collection::moveLeft] Warning: No active level set" << std::endl;
#endif
        return;
    }
    m_ActiveLevel->moveLeft();
}

// --------------------------------------------------------------
void Collection::moveRight( void )
{
    if( !m_ActiveLevel )
    {
#ifdef _DEBUG
        std::cout << "[Collection::moveRight] Warning: No active level set" << std::endl;
#endif
        return;
    }
    m_ActiveLevel->moveRight();
}

// --------------------------------------------------------------
void Collection::undo( void )
{
    if( !m_ActiveLevel )
    {
#ifdef _DEBUG
        std::cout << "[Collection::undo] Warning: No active level set" << std::endl;
#endif
        return;
    }
    m_ActiveLevel->undo();
}

// --------------------------------------------------------------
void Collection::redo( void )
{
    if( !m_ActiveLevel )
    {
#ifdef _DEBUG
        std::cout << "[Collection::redo] Warning: No active level set" << std::endl;
#endif
        return;
    }
    m_ActiveLevel->redo();
}

// --------------------------------------------------------------
void Collection::reset( void )
{
    if( !m_ActiveLevel )
    {
#ifdef _DEBUG
        std::cout << "[Collection::reset] Warning: No active level set" << std::endl;
#endif
        return;
    }
    m_ActiveLevel->reset();
    m_ActiveLevel->clearUndoData();
}

// --------------------------------------------------------------
Collection& Collection::operator=( const Collection& that )
{
    if( this == &that ) return *this;

    // shallow copies
    this->m_FileName = that.m_FileName;
    this->m_CollectionName = that.m_CollectionName;
    this->m_LevelListeners = that.m_LevelListeners;
    this->m_EnableCompression = that.m_EnableCompression;
    this->m_IsLoaded = that.m_IsLoaded;

    // destroy levels
    for( std::vector<Level*>::iterator it = m_Levels.begin(); it != m_Levels.end(); ++it )
        delete *it;
    m_Levels.clear();
    m_ActiveLevel = 0;

    // deep copy level objects
    // memory has already been allocated for level objects in copy constructor
    for( std::size_t i = 0; i != that.m_Levels.size(); ++i )
        m_Levels.push_back( new Level(*(that.m_Levels[i])) );

    std::cout << "copying collection" << std::endl;

}

} // namespace Chocobun
