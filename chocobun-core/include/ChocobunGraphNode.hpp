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
 * @brief Base class for a generic node to be part of a @a Graph
 *
 * Nodes can be arbitrarily linked with one another, making it possible to represent
 * complex data structures.
 *
 * A node holds various information about itself.
 * - A list of links (see @a GraphNodeLink) to other nodes connected with this node
 * - User defined data (can be anything)
 * - Open/closed state for a pathfinder
 * - Optional coordinate of the node
 *
 * To learn more about creating and managing graphs, please see @a Graph
 */
template <class MOVECOSTTYPE, class DATA>
class GraphNodeBase
{
public:

    typedef GraphNodeBase<MOVECOSTTYPE, DATA>           GraphNode_t;
    typedef GraphNodeLink<GraphNode_t, MOVECOSTTYPE>    GraphNodeLink_t;

protected:

    /*!
     * @brief Default constructor
     */
    GraphNodeBase( void );

    /*!
     * @brief Constructs a node and sets its data
     * See @a setData for more information
     * @param data The data to set this node to
     */
    GraphNodeBase( const DATA& data );

    /*!
     * @brief Default destructor
     */
    ~GraphNodeBase( void );

public:

    /*!
     * @brief Bidirectionally links two nodes together
     * This allows any node to be connected to any other existing node,
     * creating a complex representation of data. The link holds information
     * about how far away the two nodes are from each other, specified by
     * **moveCost**. The higher this number is, the more it costs to move
     * between nodes, thus making this link less likely to be found as an
     * optimal pathway when searching the graph.
     * @note If the linked node is destroyed at any point in the future, it
     * automatically unlinks itself again without you having to worry.
     * @param other A pointer to another node object to link to. Linking to
     * itself will silently fail. If the node being linked is already linked,
     * this will silently fail.
     * @param moveCost How far away the two nodes are distanced.
     */
    void link( GraphNode_t* other, const MOVECOSTTYPE& moveCost );

    /*!
     * @brief Unlinks two nodes that are linked
     * @note Trying to unlink a node that wasn't linked in the first place
     * will silently fail
     * @param other A pointer to another node to unlink
     */
    void unlink( GraphNode_t* other );

    /*!
     * @brief Unlinks all linked nodes
     */
    void unlinkAll( void );

    /*!
     * @brief Returns the number of links the node currently has
     * This can be useful for traversing the entire graph, as the value
     * returned can be used to jump from node to node.
     * @return The number of links the node has
     */
    std::size_t getLinkCount( void ) const;

    /*!
     * @brief Returns the link object specified by index
     * The link object is nothing more than a struct containing the linked node
     * and the movement cost of this link. See @a GraphNodeLink for more
     * information
     * @param index The index of the link. This is a number between 0 and what
     * is returned by @a getLinkCount
     * @return A @a GraphNodeLink object describing the link between this and
     * another node.
     */
    const GraphNodeLink_t& getNodeLink( const std::size_t& index ) const;

    /*!
     * @brief Sets the data this node should store
     * The data a node can store can be anything. You might want your node to
     * store tile information because your graph is part of a 2D map, or you
     * could use it for something else.
     * @param data The data this node should store
     */
    void setData( const DATA& data );

    /*!
     * @brief Gets the data this node is storing
     * This data is set by @a setData
     * @return The current data stored in this node
     */
    const DATA& getData( void ) const;

    /*!
     * @brief Sets the node to have an open state
     * This is used by the pathfinder to flag visited nodes
     */
    void open( void );

    /*!
     * @brief Sets the node to have a closed state
     * This is used by the pathdinder to flag visited nodes
     */
    void close( void );

    /*!
     * @brief Returns true if the node is open
     * This is used by the pathfinder to flag visited nodes
     */
    bool isOpen( void );

protected:

    std::vector<GraphNodeLink_t>    m_Links;
    DATA                            m_Data;
    bool                            m_IsOpen;

};

/*!
 * @brief Extended coordinate implementation if the first template parameter is not void
 *
 * If the first template parameter was not set to be **void**, a class with
 * coordinate methods is instantiated. This primarily allows the pathfinder
 * to operate much faster because it can make estimations of the remaining
 * distance
 */
template <class COORD, class MOVECOSTTYPE, class DATA>
class GraphNode : public GraphNodeBase<MOVECOSTTYPE, DATA>
{
public:

    /*!
     * @brief Default constructor
     */
    GraphNode( void );

    /*!
     * @brief Constructs a node and sets its data
     * See @a setData for more information
     * @param data The data to set this node to
     */
    GraphNode( const DATA& data );

    /*!
     * @brief Constructs a node and sets its coordinate
     * See @a setCoordinate for more information
     * @param coord The coordinate of this node
     */
    GraphNode( const COORD& coord );

    /*!
     * @brief Constructs a node and sets its coordinate and data
     * See @a setData and @a setCoordinate for more information
     * @param coord The coordinate of this node
     * @param data The data to set this node to
     */
    GraphNode( const COORD& coord, const DATA& data );

    /*!
     * @brief Default destructor
     */
    ~GraphNode( void );

    /*!
     * @brief Sets the coordinate of the node
     * The coordinate is used by the pathfinder to make estimations of the
     * remaining path, for instance, the heuristic. Some graphs won't actually
     * have any concept of "space" and as a result won't be able to have
     * coordinates for its nodes. In such a case, you may specify **void** as
     * the first template argument when instantiating the node object:
     * @code
     * Node<void, [type2], [type3]> myNode;
     *      ^
     *     here
     * @endcode
     * This causes the methods and data members for coordinates to be omitted.
     * @param coord The coordinate of this node
     */
    void setCoordinate( const COORD& coord );

    /*!
     * @brief Gets the coordinate of the node
     * This is set by @a setCoordinate
     * @return The coordinate of this node
     */
    const COORD& getCoordinate( void ) const;

private:

    COORD m_Coordinate;
};

/*!
 * @brief Non-coordinate implementation
 *
 * If the first template parameter is set to **void**, methods for coordinate
 * management are not instantiated. The pathfinder will be slower as it won't
 * be able to make any estimates about the remaining path.
 */
template <class MOVECOSTTYPE, class DATA>
class GraphNode<void, MOVECOSTTYPE, DATA> : public GraphNodeBase<MOVECOSTTYPE, DATA>
{
public:

    /*!
     * @brief Default constructor
     */
    GraphNode( void );

    /*!
     * @brief Constructs a node and sets its data
     * See @a setData for more information
     * @param data The data to set this node to
     */
    GraphNode( const DATA& data );

    /*!
     * @brief Default destructor
     */
    ~GraphNode( void );
};

} // namespace Chocobun
