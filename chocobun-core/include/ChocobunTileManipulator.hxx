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

#include <ChocobunTileManipulator.hpp>
#include <ChocobunException.hpp>

namespace Chocobun {

// --------------------------------------------------------------
template <class GRAPH, class COORD>
void TileManipulator<GRAPH,COORD>::Listener::onMoveTile( const GRAPH& graph, const COORD& oldPos, const COORD& newPos )
{
    // listener should implement this
}

// --------------------------------------------------------------
template <class GRAPH, class COORD>
void TileManipulator<GRAPH, COORD>::Listener::onSetTile( const GRAPH& graph, const COORD& pos )
{
    // listener should implement this
}

// --------------------------------------------------------------
template <class GRAPH, class COORD>
TileManipulator<GRAPH, COORD>::TileManipulator( void )
{
}

// --------------------------------------------------------------
template <class GRAPH, class COORD>
TileManipulator<GRAPH, COORD>::~TileManipulator( void )
{
}

// --------------------------------------------------------------
template <class GRAPH, class COORD>
void TileManipulator<GRAPH, COORD>::moveTile( GRAPH& graph, const COORD& oldPos, const COORD& newPos )
{
    if( this->_moveTile( graph, oldPos, newPos ) )
        this->dispatchMoveTile( graph, oldPos, newPos );
}

// --------------------------------------------------------------
template <class GRAPH, class COORD>
void TileManipulator<GRAPH, COORD>::setTile( GRAPH& graph, const COORD& pos, const typename GRAPH::Data& tile )
{
    if( this->_setTile( graph, pos, tile ) )
        this->dispatchSetTile( graph, pos );
}

// --------------------------------------------------------------
template <class GRAPH, class COORD>
void TileManipulator<GRAPH, COORD>::addListener( TileManipulator::Listener* listener )
{
    for( typename std::vector<TileManipulator::Listener*>::iterator it = m_Listeners.begin(); it != m_Listeners.end(); ++it )
        if( *it == listener )
            throw Exception( "[TileManipulator<GRAPH,COORD>::addListener] Error: Listener already registered" );
    m_Listeners.push_back( listener );
}

// --------------------------------------------------------------
template <class GRAPH, class COORD>
void TileManipulator<GRAPH, COORD>::removeListener( const TileManipulator::Listener* listener )
{
    for( typename std::vector<TileManipulator::Listener*>::iterator it = m_Listeners.begin(); it != m_Listeners.end(); ++it )
        if( *it == listener )
        {
            m_Listeners.erase( it );
            return;
        }
    throw Exception( "[TileManipulator<GRAPH,COORD>::removeListener] Error: Listener not registered" );
}

// --------------------------------------------------------------
template <class GRAPH, class COORD>
bool TileManipulator<GRAPH, COORD>::_moveTile( GRAPH& graph, const COORD& oldPos, const COORD& newPos )
{
    return false; // disable listener dispatching
}

// --------------------------------------------------------------
template <class GRAPH, class COORD>
bool TileManipulator<GRAPH, COORD>::_setTile( GRAPH& graph, const COORD& pos, const typename GRAPH::Data& tile )
{
    return false; // disable listener dispatching
}

// --------------------------------------------------------------
template <class GRAPH, class COORD>
void TileManipulator<GRAPH, COORD>::dispatchMoveTile( const GRAPH& graph, const COORD& oldPos, const COORD& newPos ) const
{
    for( typename std::vector<TileManipulator::Listener*>::const_iterator it = m_Listeners.begin(); it != m_Listeners.end(); ++it )
        (*it)->onMoveTile( graph, oldPos, newPos );
}

// --------------------------------------------------------------
template <class GRAPH, class COORD>
void TileManipulator<GRAPH, COORD>::dispatchSetTile( const GRAPH& graph, const COORD& pos ) const
{
    for( typename std::vector<TileManipulator::Listener*>::const_iterator it = m_Listeners.begin(); it != m_Listeners.end(); ++it )
        (*it)->onSetTile( graph, pos );
}

} // namespace Chocobun
