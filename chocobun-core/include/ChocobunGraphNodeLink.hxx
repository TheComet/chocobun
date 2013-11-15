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
// GraphNodeLink.hxx
// --------------------------------------------------------------

// --------------------------------------------------------------
// include files

#include <ChocobunGraphNodeLink.hpp>

namespace Chocobun {

// --------------------------------------------------------------
template <class LINK, class MOVECOSTTYPE>
GraphNodeLink<LINK,MOVECOSTTYPE>::GraphNodeLink( void ) :
    link( 0 ),
    moveCost( MOVECOSTTYPE() )
{
}

// --------------------------------------------------------------
template <class LINK, class MOVECOSTTYPE>
GraphNodeLink<LINK,MOVECOSTTYPE>::GraphNodeLink( LINK* link, const MOVECOSTTYPE& moveCost) :
    link( link ),
    moveCost( moveCost )
{
}

} // namespace Chocobun
