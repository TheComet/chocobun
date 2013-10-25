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
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with Chocobun. If not, see <http://www.gnu.org/licenses/>.
*/

// --------------------------------------------------------------
// TileManipulator.cpp
// --------------------------------------------------------------

// --------------------------------------------------------------
// include files

#include <core/TileManipulator.hpp>
#include <core/Exception.hpp>

namespace Chocobun {

// --------------------------------------------------------------
template <class COORD>
void TileManipulator<COORD>::Listener::onMoveTile( const COORD& oldPos, const COORD& newPos )
{
    // listener should implement this
}

// --------------------------------------------------------------
template <class COORD>
void TileManipulator<COORD>::Listener::onSetTile( const COORD& pos, const char& tile )
{
    // listener should implement this
}

// --------------------------------------------------------------
template <class COORD>
TileManipulator<COORD>::TileManipulator( void )
{
}

// --------------------------------------------------------------
template <class COORD>
TileManipulator<COORD>::~TileManipulator( void )
{
}

// --------------------------------------------------------------
template <class COORD>
void TileManipulator<COORD>::moveTile( const COORD& oldPos, const COORD& newPos ) const
{
    if( this->_moveTile( oldPos, newPos ) )
        this->dispatchMoveTile( oldPos, newPos );
}

// --------------------------------------------------------------
template <class COORD>
void TileManipulator<COORD>::setTile( const COORD& pos, const char& tile ) const
{
    if( this->_setTile( pos, tile ) )
        this->dispatchSetTile( pos, tile );
}

// --------------------------------------------------------------
template <class COORD>
void TileManipulator<COORD>::addListener( const TileManipulator::Listener* listener )
{
    for( typename std::vector<TileManipulator::Listener*>::iterator it = m_Listeners.begin(); it != m_Listeners.end(); ++it )
        if( *it == listener )
            throw Exception( "[TileManipulator::addListener] Error: Listener already registered" );
    m_Listeners.push_back( listener );
}

// --------------------------------------------------------------
template <class COORD>
void TileManipulator<COORD>::removeListener( const TileManipulator::Listener* listener )
{
    for( typename std::vector<TileManipulator::Listener*>::iterator it = m_Listeners.begin(); it != m_Listeners.end(); ++it )
        if( *it == listener )
        {
            m_Listeners.erase( it );
            return;
        }
    throw Exception( "[TileManipulator::removeListener] Error: Listener not registered" );
}

// --------------------------------------------------------------
template <class COORD>
bool TileManipulator<COORD>::_moveTile( const COORD& oldPos, const COORD& newPos )
{
    return false; // disable listener dispatching
}

// --------------------------------------------------------------
template <class COORD>
bool TileManipulator<COORD>::_setTile( const COORD& pos, const char& tile )
{
    return false; // disable listener dispatching
}

// --------------------------------------------------------------
template <class COORD>
void TileManipulator<COORD>::dispatchMoveTile( const COORD& oldPos, const COORD& newPos ) const
{
    for( typename std::vector<TileManipulator::Listener*>::const_iterator it = m_Listeners.begin(); it != m_Listeners.end(); ++it )
        (*it)->onMoveTile( oldPos, newPos );
}

// --------------------------------------------------------------
template <class COORD>
void TileManipulator<COORD>::dispatchSetTile( const COORD& pos, const char& tile ) const
{
    for( typename std::vector<TileManipulator::Listener*>::const_iterator it = m_Listeners.begin(); it != m_Listeners.end(); ++it )
        (*it)->onSetTile( pos, tile );
}

} // namespace Chocobun
