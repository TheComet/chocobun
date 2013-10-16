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
// CollectionParserListener.hpp
// --------------------------------------------------------------

#ifndef __CHOCOBUN_CORE_COLLECTION_PARSER_LISTENER_HPP__
#define __CHOCOBUN_CORE_COLLECTION_PARSER_LISTENER_HPP__

// --------------------------------------------------------------
// include files

#include <string>

namespace Chocobun {

// --------------------------------------------------------------
// forward declarations

class Level;

/*!
 * @brief Provides an interface for classes to receive events from the parser
 */
class CollectionParserListener
{
public:

    /*!
     * @brief Default constructor
     */
    CollectionParserListener( void ) {}

    /*!
     * @brief Default Destructor
     */
    virtual ~CollectionParserListener( void ) {}

    /*!
     * @brief Requests construction of a new Level object
     * It is unclean for the parser to construct a new Level object for higher
     * classes. Therefore, the parser will call this method instead, requesting
     * construction of one. The class implementing this interface is
     * responsible for the construction and destruction of it.
     * @return Should return a pointer to the newly constructed LEvel object
     */
    virtual Level* _constructNewLevel( void ) = 0;

    /*!
     * @brief Auto-generates a level name if the provided string is empty
     * This is implemented by whichever class manages all of the levels.
     * @param name The current level name extracted by the parser (can also be
     * an empty string, in which case the name should be generated )
     */
    virtual void _generateLevelName( std::string& name ) = 0;
};

} // namespace Chocobun

#endif // __CHOCOBUN_CORE_COLLECTION_PARSER_LISTENER_HPP__
