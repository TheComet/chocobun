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
// Graph.hpp
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

    /*!
     * @brief Default constructor
     */
    Graph( void );

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

private:
    std::vector<GraphNode<T>*> m_Nodes;
};

} // namespace Chocobun
