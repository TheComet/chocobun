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

#include <vector>

namespace Chocobun {

/*!
 * @brief A generic node to be part of a graph for various searching algorithms
 */
template <class T>
class GraphNode
{
public:

    /*!
     * @brief Default constructor
     */
    GraphNode( void );

    /*!
     * @brief Constructors a node and sets its data
     */
    GraphNode( const T& data );

    /*!
     * @brief Default destructor
     */
    ~GraphNode( void );

    /*!
     * @brief Bidirectionally links two nodes together
     */
    void link( GraphNode<T>* other );

    /*!
     * @brief Unlinks two nodes that are linked
     */
    void unlink( GraphNode* other );

    /*!
     * @brief Unlinks all linked nodes
     */
    void unlinkAll( void );

    /*!
     * @brief Returns the number of links the node currently has
     */
    std::size_t getLinkCount( void ) const;

    /*!
     * @brief Returns a pointer to a linked node specified by index
     */
    GraphNode<T>* getLinkedNode( const std::size_t& index );

    /*!
     * @brief Returns a const pointer to a linked node specified by index
     */
    const GraphNode<T>* getLinkedNode( const std::size_t& index ) const;

    /*!
     * @brief Sets the data this node should store
     */
    void setData( const T& data );

    /*!
     * @brief Gets the data this node is storing
     */
    const T& getData( void ) const;

private:

    std::vector<GraphNode*> m_Links;
    T                       m_Data;

};

} // namespace Chocobun
