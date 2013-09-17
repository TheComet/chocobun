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
// Collection
// --------------------------------------------------------------

// --------------------------------------------------------------
// include files

#include <core/Collection.hpp>
#include <core/CollectionParser.hpp>

#include <iostream>
#include <core/Level.hpp>

namespace Sokoban {

// --------------------------------------------------------------
Collection::Collection( const std::string& fileName ) :
    m_FileName( fileName ),
    m_EnableCompression( false ),
    m_IsInitialised( false )
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

} // namespace Sokoban
