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
template <class COORD, class MOVECOSTTYPE, class DATA>
GraphNode<COORD, MOVECOSTTYPE, DATA>::GraphNode( void ) :
    m_Links(),
    m_Coordinate( COORD() ),
    m_Data( DATA() )
{
}

// --------------------------------------------------------------
template <class COORD, class MOVECOSTTYPE, class DATA>
GraphNode<COORD, MOVECOSTTYPE, DATA>::GraphNode( const DATA& content ) :
    m_Links(),
    m_Coordinate( COORD() ),
    m_Data( content )
{
}

// --------------------------------------------------------------
template <class COORD, class MOVECOSTTYPE, class DATA>
GraphNode<COORD, MOVECOSTTYPE, DATA>::GraphNode( const COORD& coord ) :
    m_Links(),
    m_Coordinate( coord ),
    m_Data( DATA() )
{
}

// --------------------------------------------------------------
template <class COORD, class MOVECOSTTYPE, class DATA>
GraphNode<COORD, MOVECOSTTYPE, DATA>::GraphNode( const COORD& coord, const DATA& data ) :
    m_Links(),
    m_Coordinate( coord ),
    m_Data( data )
{
}

// --------------------------------------------------------------
template <class COORD, class MOVECOSTTYPE, class DATA>
GraphNode<COORD, MOVECOSTTYPE, DATA>::~GraphNode( void )
{
    this->unlinkAll();
}

// --------------------------------------------------------------
template <class COORD, class MOVECOSTTYPE, class DATA>
void GraphNode<COORD, MOVECOSTTYPE, DATA>::link( GraphNode_t* other, const MOVECOSTTYPE& moveCost )
{

    // self linkage
    if( this == other ) return;

    // this already linked with other
    for( typename std::vector<GraphNodeLink_t>::iterator it = m_Links.begin(); it != m_Links.end(); ++it )
        if( it->link == other ) return;

    // safe to link both, as if this isn't linked with the other, the other is
    // guaranteed not be be linked with this
    this->m_Links.push_back( GraphNodeLink_t(other, moveCost) );
    other->m_Links.push_back( GraphNodeLink_t(this, moveCost) );
}

// --------------------------------------------------------------
template <class COORD, class MOVECOSTTYPE, class DATA>
void GraphNode<COORD, MOVECOSTTYPE, DATA>::unlink( GraphNode_t* other )
{

    // unlink this from other
    for( typename std::vector<GraphNodeLink_t>::iterator it = this->m_Links.begin(); it != this->m_Links.end(); ++it )
        if( it->link == other )
        {
            m_Links.erase( it );
            break;
        }

    // unlink other from this
    for( typename std::vector<GraphNodeLink_t>::iterator it = other->m_Links.begin(); it != other->m_Links.end(); ++it )
        if( it->link == this )
        {
            other->m_Links.erase( it );
            break;
        }
}

// --------------------------------------------------------------
template <class COORD, class MOVECOSTTYPE, class DATA>
void GraphNode<COORD, MOVECOSTTYPE, DATA>::unlinkAll( void )
{
    typename std::vector<GraphNodeLink_t>::iterator it = this->m_Links.begin();
    while( it != this->m_Links.end() )
    {

        // unlink other from this
        for( typename std::vector<GraphNodeLink_t>::iterator it2 = it->link->m_Links.begin(); it2 != it->link->m_Links.end(); ++it2 )
            if( it2->link == this )
            {
                it->link->m_Links.erase( it2 );
                break;
            }

        // unlink this from other
        it = this->m_Links.erase( it );
    }
}

// --------------------------------------------------------------
template <class COORD, class MOVECOSTTYPE, class DATA>
std::size_t GraphNode<COORD, MOVECOSTTYPE, DATA>::getLinkCount( void ) const
{
    return this->m_Links.size();
}

// --------------------------------------------------------------
template <class COORD, class MOVECOSTTYPE, class DATA>
const GraphNodeLink< GraphNode<COORD, MOVECOSTTYPE, DATA>, MOVECOSTTYPE >&
    GraphNode<COORD, MOVECOSTTYPE, DATA>::getNodeLink( const std::size_t& index ) const
{
    return this->m_Links.at( index );
}

// --------------------------------------------------------------
template <class COORD, class MOVECOSTTYPE, class DATA>
void GraphNode<COORD, MOVECOSTTYPE, DATA>::setCoordinate( const COORD& coord )
{
    this->m_Coordinate = coord;
}

// --------------------------------------------------------------
template <class COORD, class MOVECOSTTYPE, class DATA>
const COORD& GraphNode<COORD, MOVECOSTTYPE, DATA>::getCoordinate( void ) const
{
    return this->m_Coordinate;
}

// --------------------------------------------------------------
template <class COORD, class MOVECOSTTYPE, class DATA>
void GraphNode<COORD, MOVECOSTTYPE, DATA>::setData( const DATA& data )
{
    this->m_Data = data;
}

// --------------------------------------------------------------
template <class COORD, class MOVECOSTTYPE, class DATA>
const DATA& GraphNode<COORD, MOVECOSTTYPE, DATA>::getData( void ) const
{
    return this->m_Data;
}

} // namespace Chocobun
