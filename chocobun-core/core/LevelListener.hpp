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
// Level
// --------------------------------------------------------------

#ifndef __CHOCOBUN_CORE_LEVEL_LISTENER_HPP__
#define __CHOCOBUN_CORE_LEVEL_LISTENER_HPP__

// --------------------------------------------------------------
// include files

#include <core/Config.hpp>

namespace Chocobun {

/*!
 * @brief Listener interface class
 * Allows other objects to register and listen to level events
 */
class LevelListener
{
public:

    /*!
     * @brief When a tile changes its type
     */
    virtual void onSetTile( const std::size_t& x, const std::size_t& y, const char& tile ){}

    /*!
     * @brief When a tile moves from an old position to a new position
     */
    virtual void onMoveTile( const std::size_t& oldX, const std::size_t& oldY, const std::size_t& newX, const std::size_t& newY ){}

};

} // namespace Chocobun

#endif // __CHOCOBUN_CORE_LEVEL_HPP__
