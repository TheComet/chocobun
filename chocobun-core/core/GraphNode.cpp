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
// GraphNode.hpp
// --------------------------------------------------------------

// --------------------------------------------------------------
// include files

#include <core/GraphNode.hpp>

namespace Chocobun {

// --------------------------------------------------------------
template <class T>
GraphNode<T>::GraphNode( void )
{
}

// --------------------------------------------------------------
template <class T>
GraphNode<T>::~GraphNode( void )
{
    this->unlinkAll();
}

// --------------------------------------------------------------
template <class T>
void GraphNode<T>::link( const GraphNode* other )
{

    // self linkage
    if( this == other ) return;

    // this already linked with other
    for( typename std::vector<GraphNode*>::iterator it = m_Links.begin(); it != m_Links.end(); ++it )
        if( *it == other ) return;

    // safe to link both, as if this isn't linked with the other, the other is
    // guaranteed not be be linked with this
    m_Links.push_back( other );
    other->m_Links.push_back( this );
}

// --------------------------------------------------------------
template <class T>
void GraphNode<T>::unlink( const GraphNode* other )
{

    // self linkage
    if( this == other ) return;

    // not linked
    typename std::vector<GraphNode*>::iterator it = m_Links.begin();
    for( ; it != m_Links.end(); ++it )
        if( *it == other )
            break;
    if( it == m_Links.end() )
        return;

    // unlink
    m_Links.erase( it );
    other->unlink( this );
}

// --------------------------------------------------------------
template <class T>
void GraphNode<T>::unlinkAll( void )
{
    typename std::vector<GraphNode*>::iterator it = m_Links.begin();
    GraphNode* toUnlink;
    while( it != m_Links.end() )
    {
        toUnlink = *it;
        it = m_Links.erase( it );
        toUnlink->unlink( this );
    }
}

} // namespace Chocobun
