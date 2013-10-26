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

#include <ChocobunGraphNode.hpp>

namespace Chocobun {

// --------------------------------------------------------------
template <class T>
GraphNode<T>::GraphNode( void ) :
    m_Links(),
    m_Data( T() )
{
}

// --------------------------------------------------------------
template <class T>
GraphNode<T>::GraphNode( const T& content ) :
    m_Links(),
    m_Data( content )
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
void GraphNode<T>::link( GraphNode<T>* other )
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
void GraphNode<T>::unlink( GraphNode* other )
{

    // unlink this from other
    for( typename std::vector<GraphNode*>::iterator it = m_Links.begin(); it != m_Links.end(); ++it )
        if( *it == other )
        {
            m_Links.erase( it );
            break;
        }

    // unlink other from this
    for( typename std::vector<GraphNode*>::iterator it = other->m_Links.begin(); it != other->m_Links.end(); ++it )
        if( *it == this )
        {
            other->m_Links.erase( it );
            break;
        }
}

// --------------------------------------------------------------
template <class T>
void GraphNode<T>::unlinkAll( void )
{
    typename std::vector<GraphNode*>::iterator it = m_Links.begin();
    while( it != m_Links.end() )
    {

        // unlink other from this
        for( typename std::vector<GraphNode*>::iterator it2 = (*it)->m_Links.begin(); it2 != (*it)->m_Links.end(); ++it2 )
            if( *it2 == this )
            {
                (*it)->m_Links.erase( it2 );
                break;
            }

        // unlink this from other
        it = m_Links.erase( it );
    }
}

// --------------------------------------------------------------
template <class T>
std::size_t GraphNode<T>::getLinkCount( void ) const
{
    return m_Links.size();
}

// --------------------------------------------------------------
template <class T>
GraphNode<T>* GraphNode<T>::getLinkedNode( const std::size_t& index)
{
    return m_Links.at( index );
}

// --------------------------------------------------------------
template <class T>
const GraphNode<T>* GraphNode<T>::getLinkedNode( const std::size_t& index ) const
{
    return m_Links.at( index );
}

// --------------------------------------------------------------
template <class T>
void GraphNode<T>::setData( const T& data )
{
    this->m_Data = data;
}

// --------------------------------------------------------------
template <class T>
const T& GraphNode<T>::getData( void ) const
{
    return this->m_Data;
}

} // namespace Chocobun
