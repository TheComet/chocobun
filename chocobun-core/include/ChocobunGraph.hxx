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
#include <ChocobunGraphNode.hpp>

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
GraphNode<T>* Graph<T>::getNodePtr( const std::size_t& ID )
{
    return m_Nodes.at( ID );
}

// --------------------------------------------------------------
template <class T>
GraphNode<T>& Graph<T>::getNode( const std::size_t& ID )
{
    return *this->getNodePtr( ID );
}

// --------------------------------------------------------------
template <class T>
Graph<T>* Graph<T>::operator=( const Graph<T>& that )
{
    // le pain
}

} // namespace Chocobun
