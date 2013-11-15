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
// GraphNodeLink.hpp
// --------------------------------------------------------------

namespace Chocobun {

// --------------------------------------------------------------
// forward declarations

template <class COORD, class MOVECOSTTYPE, class DATA>
class GraphNode;

/*!
 * @brief
 */
template <class LINK, class MOVECOSTTYPE>
class GraphNodeLink
{

    /*!
     * @brief Default constructor
     * @note Made private to force construction with parameters
     */
    GraphNodeLink( void );

public:

    /*!
     * @brief Constructs a link with another node and the specified move cost
     */
    GraphNodeLink( LINK* link, const MOVECOSTTYPE& moveCost );

    LINK*           link;
    MOVECOSTTYPE    moveCost;
};

} // namespace Chocobun
