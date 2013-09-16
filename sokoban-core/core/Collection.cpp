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
    m_FileName( fileName )
{
}

// --------------------------------------------------------------
Collection::~Collection( void )
{
}

// --------------------------------------------------------------
void Collection::initialise( void )
{

    // load and parse levels
    CollectionParser cp;
    cp.parse( m_FileName, m_LevelMap );
}

// --------------------------------------------------------------
void Collection::deinitialise( void )
{

    // export levels
    CollectionParser cp;
    cp.save( m_FileName + "out", m_LevelMap );
}

// --------------------------------------------------------------
void Collection::setName( const std::string& name )
{
    m_CollectionName = name;
}

} // namespace Sokoban
