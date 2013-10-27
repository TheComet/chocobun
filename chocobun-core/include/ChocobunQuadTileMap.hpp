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
// ChocobunQuadTileMap.hpp
// --------------------------------------------------------------

// --------------------------------------------------------------
// include files

#include <ChocobunGraph.hxx>

namespace Chocobun {

// --------------------------------------------------------------
// forward declarations

template <class T>
class QuadTileMap
{

    /*!
     * @brief Default constructor
     */
    QuadTileMap( void );

    /*!
     * @brief Default destructor
     */
    ~QuadTileMap( void );

    /*!
     * @brief Returns a reference to the underlying graph
     */
    Graph<T>& getGraph( void );

    /*!
     * @brief Returns a const reference to the underlying graph
     */
    const Graph<T>& getGraph( void ) const;

private:

    Graph<T> m_Graph;

};

} // namespace Chocobun
