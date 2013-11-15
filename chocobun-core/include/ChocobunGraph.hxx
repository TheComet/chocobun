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
// ChocobunGraph.hxx
// --------------------------------------------------------------

// --------------------------------------------------------------
// include files

#include <ChocobunGraph.hpp>
#include <ChocobunGraphNode.hxx>
#include <ChocobunException.hpp>

#include <iostream>

namespace Chocobun {

// --------------------------------------------------------------
template <class NODE>
Graph<NODE>::Graph( void )
{
}

// --------------------------------------------------------------
template <class NODE>
Graph<NODE>::Graph( const Graph<NODE>& that )
{
    *this = that;
}

// --------------------------------------------------------------
template <class NODE>
Graph<NODE>::~Graph( void )
{
    this->removeAllNodes();
}

// --------------------------------------------------------------
template <class NODE>
NODE* Graph<NODE>::addNode( void )
{
    NODE* newNode = new NODE();
    m_Nodes.push_back( newNode );
    return newNode;
}

// --------------------------------------------------------------
template <class NODE>
void Graph<NODE>::removeNode( NODE* node )
{
    for( typename std::vector<NODE*>::iterator it = m_Nodes.begin(); it != m_Nodes.end(); ++it )
        if( *it == node )
        {
            m_Nodes.erase( it );
            return;
        }
}

// --------------------------------------------------------------
template <class NODE>
void Graph<NODE>::removeAllNodes( void )
{
    for( typename std::vector<NODE*>::iterator it = m_Nodes.begin(); it != m_Nodes.end(); ++it )
        delete *it;
    m_Nodes.clear();
}

// --------------------------------------------------------------
template <class NODE>
std::size_t Graph<NODE>::getNodeCount( void ) const
{
    return m_Nodes.size();
}

// --------------------------------------------------------------
template <class NODE>
std::size_t Graph<NODE>::getNodeIndex( const NODE* node ) const
{
    for( std::size_t i = 0; i != m_Nodes.size(); ++i )
        if( m_Nodes[i] == node )
            return i;
    throw Exception( "[Graph<NODE>::getNodeIndex] Error: Node not found" );
}

// --------------------------------------------------------------
template <class NODE>
NODE* Graph<NODE>::getNodePtr( const std::size_t& index )
{
    return m_Nodes.at( index );
}

// --------------------------------------------------------------
template <class NODE>
const NODE* Graph<NODE>::getNodePtr( const std::size_t& index ) const
{
    return m_Nodes.at( index );
}

// --------------------------------------------------------------
template <class NODE>
NODE& Graph<NODE>::getNode( const std::size_t& index )
{
    return *m_Nodes.at( index );
}

// --------------------------------------------------------------
template <class NODE>
const NODE& Graph<NODE>::getNode( const std::size_t& index ) const
{
    return *m_Nodes.at( index );
}

// --------------------------------------------------------------
template <class NODE>
Graph<NODE>& Graph<NODE>::operator=( const Graph<NODE>& that )
{
    if( &that == this ) return *this;

    // re-allocate memory to match as many nodes as "that"
    this->removeAllNodes();
    for( std::size_t i = 0; i != that.getNodeCount(); ++i )
        m_Nodes.push_back( new NODE() );

    // build links
    // assumption is the indices of both m_Nodes lists in this and that are identical
    for( std::size_t i = 0; i != m_Nodes.size(); ++i )
    {
        for( std::size_t l = 0; l != that.getNode(i).getLinkCount(); ++l )
        {
            const std::size_t mutualIndexOfLink = that.getNodeIndex( that.getNode(i).getNodeLink(l).link );
            m_Nodes[i]->link( m_Nodes[mutualIndexOfLink], that.getNode(i).getNodeLink(l).moveCost );
        }
    }

    return *this;
}

} // namespace Chocobun
