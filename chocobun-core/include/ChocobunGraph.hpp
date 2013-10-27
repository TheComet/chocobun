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
// ChocobunGraph.hpp
// --------------------------------------------------------------

// --------------------------------------------------------------
// include files

#include <vector>

namespace Chocobun {

// --------------------------------------------------------------
// forward declarations

template <class T>
class GraphNode;

template <class T>
class Graph
{
public:

    typedef T Data;

    /*!
     * @brief Default constructor
     */
    Graph( void );

    /*!
     * @brief Copy constructor
     */
    Graph( const Graph<T>& that );

    /*!
     * @brief Default destructor
     */
    ~Graph( void );

    /*!
     * @brief Adds a node to the graph
     */
    GraphNode<T>* addNode( void );

    /*!
     * @brief Removes a node from the graph
     */
    void removeNode( GraphNode<T>* node );

    /*!
     * @brief Removes all nodes from the graph
     */
    void removeAllNodes( void );

    /*!
     * @brief Returns the number of nodes in the graph
     */
    std::size_t getNodeCount( void ) const;

    /*!
     * @brief Returns the current index of the node
     */
    std::size_t getNodeIndex( const GraphNode<T>* node ) const;

    /*!
     * @brief Returns a pointer to the specified node
     */
    GraphNode<T>* getNodePtr( const std::size_t& index );

    /*!
     * @brief Returns a const pointer to the specified node
     */
    const GraphNode<T>* getNodePtr( const std::size_t& index ) const;

    /*!
     * @brief Returns a reference to the specified node
     */
    GraphNode<T>& getNode( const std::size_t& index );

    /*!
     * @brief Returns a const reference to the specified node
     */
    const GraphNode<T>& getNode( const std::size_t& index ) const;

    /*!
     * @brief Overload assignment operator
     */
    Graph<T>& operator=( const Graph<T>& that );

private:
    std::vector<GraphNode<T>*> m_Nodes;
};

} // namespace Chocobun
