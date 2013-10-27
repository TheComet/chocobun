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
template <class T>
Graph<T>::Graph( void )
{
}

// --------------------------------------------------------------
template <class T>
Graph<T>::Graph( const Graph<T>& that )
{
    *this = that;
}

// --------------------------------------------------------------
template <class T>
Graph<T>::~Graph( void )
{
    this->removeAllNodes();
}

// --------------------------------------------------------------
template <class T>
GraphNode<T>* Graph<T>::addNode( void )
{
    GraphNode<T>* newNode = new GraphNode<T>();
    m_Nodes.push_back( newNode );
    return newNode;
}

// --------------------------------------------------------------
template <class T>
void Graph<T>::removeNode( GraphNode<T>* node )
{
    for( typename std::vector<GraphNode<T>*>::iterator it = m_Nodes.begin(); it != m_Nodes.end(); ++it )
        if( *it == node )
        {
            m_Nodes.erase( it );
            return;
        }
}

// --------------------------------------------------------------
template <class T>
void Graph<T>::removeAllNodes( void )
{
    for( typename std::vector<GraphNode<T>*>::iterator it = m_Nodes.begin(); it != m_Nodes.end(); ++it )
        delete *it;
    m_Nodes.clear();
}

// --------------------------------------------------------------
template <class T>
std::size_t Graph<T>::getNodeCount( void ) const
{
    return m_Nodes.size();
}

// --------------------------------------------------------------
template <class T>
std::size_t Graph<T>::getNodeIndex( const GraphNode<T>* node ) const
{
    for( std::size_t i = 0; i != m_Nodes.size(); ++i )
        if( m_Nodes[i] == node )
            return i;
    throw Exception( "[Graph<T>::getNodeIndex] Error: Node not found" );
}

// --------------------------------------------------------------
template <class T>
GraphNode<T>* Graph<T>::getNodePtr( const std::size_t& index )
{
    return m_Nodes.at( index );
}

// --------------------------------------------------------------
template <class T>
const GraphNode<T>* Graph<T>::getNodePtr( const std::size_t& index ) const
{
    return m_Nodes.at( index );
}

// --------------------------------------------------------------
template <class T>
GraphNode<T>& Graph<T>::getNode( const std::size_t& index )
{
    return *m_Nodes.at( index );
}

// --------------------------------------------------------------
template <class T>
const GraphNode<T>& Graph<T>::getNode( const std::size_t& index ) const
{
    return *m_Nodes.at( index );
}

// --------------------------------------------------------------
template <class T>
Graph<T>& Graph<T>::operator=( const Graph<T>& that )
{
    if( &that == this ) return *this;

    // re-allocate memory to match as many nodes as "that"
    this->removeAllNodes();
    for( std::size_t i = 0; i != that.getNodeCount(); ++i )
        m_Nodes.push_back( new GraphNode<T>() );

    // build links
    // assumption is the indices of both m_Nodes lists are identical
    for( std::size_t i = 0; i != m_Nodes.size(); ++i )
    {
        for( std::size_t l = 0; l != that.getNode(i).getLinkCount(); ++l )
        {
            const std::size_t mutualIndexOfLink = that.getNodeIndex( that.getNode(i).getLinkedNode(l) );
            m_Nodes[i]->link( m_Nodes[mutualIndexOfLink] );
        }
    }

    return *this;
}

} // namespace Chocobun
