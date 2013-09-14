/*
 * This file is part of Sokoban.
 *
 * Sokoban is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Sokoban is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Sokoban.  If not, see <http://www.gnu.org/licenses/>.
 */

// --------------------------------------------------------------
// define export macros
// --------------------------------------------------------------

#ifndef __SOKOBAN_CORE_EXPORT_HPP__
#   define __SOKOBAN_CORE_EXPORT_HPP__

    // headers
#   include <core/Config.hpp>

#   if defined(SOKOBAN_CORE_DYNAMIC)
#       define SOKOBAN_CORE_API SOKOBAN_CORE_EXPORT
#   else
#       define SOKOBAN_CORE_API SOKOBAN_CORE_IMPORT
#   endif

#endif // __SOKOBAN_CORE_EXPORT_HPP__
