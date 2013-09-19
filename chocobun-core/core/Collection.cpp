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
// Collection
// --------------------------------------------------------------

// --------------------------------------------------------------
// include files

#include <core/Collection.hpp>
#include <core/CollectionParser.hpp>
#include <core/Exception.hpp>

#include <iostream>
#include <core/Level.hpp>

namespace Chocobun {

// --------------------------------------------------------------
Collection::Collection( const std::string& fileName ) :
    m_FileName( fileName ),
    m_EnableCompression( false ),
    m_IsInitialised( false ),
    m_ActiveLevel( 0 )
{
}

// --------------------------------------------------------------
Collection::~Collection( void )
{
    this->deinitialise();
}

// --------------------------------------------------------------
void Collection::initialise( void )
{

    if( m_IsInitialised ) return;

    // load and parse levels
    CollectionParser cp;
    m_CollectionName = cp.parse( m_FileName, m_Levels );

    m_IsInitialised = true;
}

// --------------------------------------------------------------
void Collection::deinitialise( void )
{

    if( !m_IsInitialised ) return;

    // export levels
    CollectionParser cp;
    cp.save( m_CollectionName, m_FileName, m_Levels, m_EnableCompression );

    // unload levels
    for( std::vector<Level*>::iterator it = m_Levels.begin(); it != m_Levels.end(); ++it )
        delete *it;
    m_Levels.clear();
    m_ActiveLevel = 0;

    m_IsInitialised = false;
}

// --------------------------------------------------------------
void Collection::setName( const std::string& name )
{
    m_CollectionName = name;
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
void Collection::getLevelNames( std::vector<std::string>& vs )
{
    vs.clear();
    for( std::vector<Level*>::iterator it = m_Levels.begin(); it != m_Levels.end(); ++it )
        vs.push_back( (*it)->getLevelName() );
}

// --------------------------------------------------------------
void Collection::streamLevelNames( std::ostream& stream )
{
    for( std::vector<Level*>::iterator it = m_Levels.begin(); it != m_Levels.end(); ++it )
        stream << (*it)->getLevelName() << std::endl;
}

// --------------------------------------------------------------
bool Collection::setActiveLevel( const std::string& levelName )
{
    for( std::vector<Level*>::iterator it = m_Levels.begin(); it != m_Levels.end(); ++it )
    {
        if( (*it)->getLevelName().compare( levelName ) == 0 )
        {
            m_ActiveLevel = (*it);
            return true;
        }
    }
    return false;
}

// --------------------------------------------------------------
bool Collection::hasActiveLevel( void )
{
    if( m_ActiveLevel ) return true;
    return false;
}

// --------------------------------------------------------------
const std::vector< std::vector<char> >& Collection::getTileData( void ) const
{
    if( !m_ActiveLevel) throw Exception( "[Collection::getTileData] Attempt to get tile data without first setting an active level" );
    return m_ActiveLevel->getTileData();
}

// --------------------------------------------------------------
void Collection::streamTileData( std::ostream& stream )
{
    if( !m_ActiveLevel) return;
    m_ActiveLevel->streamAllTileData( stream );
}

// --------------------------------------------------------------
char Collection::getTile( Uint32 x, Uint32 y )
{
    if( !m_ActiveLevel ) return '\0';
    return m_ActiveLevel->getTile( x, y );
}

// --------------------------------------------------------------
Uint32 Collection::getSizeX( void ) const
{
    if( !m_ActiveLevel ) return 0;
    return m_ActiveLevel->getSizeX();
}

// --------------------------------------------------------------
Uint32 Collection::getSizeY( void ) const
{
    if( !m_ActiveLevel ) return 0;
    return m_ActiveLevel->getSizeY();
}

// --------------------------------------------------------------
bool Collection::validateLevel( void ) const
{
    if( !m_ActiveLevel ) return false;
    return m_ActiveLevel->validateLevel();
}

// --------------------------------------------------------------
void Collection::moveUp( void )
{
    if( !m_ActiveLevel ) return;
    m_ActiveLevel->moveUp();
}

// --------------------------------------------------------------
void Collection::moveDown( void )
{
    if( !m_ActiveLevel ) return;
    m_ActiveLevel->moveDown();
}

// --------------------------------------------------------------
void Collection::moveLeft( void )
{
    if( !m_ActiveLevel ) return;
    m_ActiveLevel->moveLeft();
}

// --------------------------------------------------------------
void Collection::moveRight( void )
{
    if( !m_ActiveLevel ) return;
    m_ActiveLevel->moveRight();
}

// --------------------------------------------------------------
void Collection::undo( void )
{
    if( !m_ActiveLevel ) return;
    m_ActiveLevel->undo();
}

// --------------------------------------------------------------
void Collection::redo( void )
{
    if( !m_ActiveLevel ) return;
    m_ActiveLevel->redo();
}

} // namespace Chocobun
