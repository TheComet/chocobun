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
#include <ChocobunGraphNodeLink.hxx>

namespace Chocobun {

/*!
 * @brief A generic node to be part of a graph for various searching algorithms
 */
template <class COORD, class MOVECOSTTYPE, class DATA>
class GraphNode
{
public:

    typedef GraphNode<COORD, MOVECOSTTYPE, DATA>        GraphNode_t;
    typedef GraphNodeLink<GraphNode_t, MOVECOSTTYPE>    GraphNodeLink_t;

    /*!
     * @brief Default constructor
     */
    GraphNode( void );

    /*!
     * @brief Constructors a node and sets its data
     */
    GraphNode( const DATA& data );

    /*!
     * @brief Constructs a node and sets its coordinate
     */
    GraphNode( const COORD& coord );

    /*!
     * @brief Constructs a node and sets its coordinate and data
     */
    GraphNode( const COORD& coord, const DATA& data );

    /*!
     * @brief Default destructor
     */
    ~GraphNode( void );

    /*!
     * @brief Bidirectionally links two nodes together
     */
    void link( GraphNode_t* other, const MOVECOSTTYPE& moveCost );

    /*!
     * @brief Unlinks two nodes that are linked
     */
    void unlink( GraphNode_t* other );

    /*!
     * @brief Unlinks all linked nodes
     */
    void unlinkAll( void );

    /*!
     * @brief Returns the number of links the node currently has
     */
    std::size_t getLinkCount( void ) const;

    /*!
     * @brief Returns the link object specified by index
     */
    const GraphNodeLink_t& getNodeLink( const std::size_t& index ) const;

    /*!
     * @brief Sets the coordinate of the node
     */
    void setCoordinate( const COORD& coord );

    /*!
     * @brief Gets the coordinate of the node
     */
    const COORD& getCoordinate( void ) const;

    /*!
     * @brief Sets the data this node should store
     */
    void setData( const DATA& data );

    /*!
     * @brief Gets the data this node is storing
     */
    const DATA& getData( void ) const;

private:

    std::vector<GraphNodeLink_t>    m_Links;
    COORD                           m_Coordinate;
    DATA                            m_Data;

};

} // namespace Chocobun
