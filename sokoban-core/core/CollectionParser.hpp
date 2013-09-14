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
// Collection Parser
// --------------------------------------------------------------

#ifndef __SOKOBAN_CORE_COLLECTION_PARSER_HPP__
#define __SOKOBAN_CORE_COLLECTION_PARSER_HPP__

// --------------------------------------------------------------
// include files

#include <map>
#include <string>

namespace Sokoban {

// --------------------------------------------------------------
// forward declarations

class Level;

/*!
 * @brief Parses a collection and loads all levels into an internal format
 */
class CollectionParser
{
public:

    /*!
     * @brief Constructor
     */
    CollectionParser( void );

    /*!
     * @brief Destructor
     */
    ~CollectionParser( void );

    /*!
     * @brief Parses a collection file and writes into a map of levels
     */
    void parse( const std::string& fileName, std::map<std::string, Level*>& levelMap );

private:

    /*!
     * @brief Universal .SOK format parser
     *
     * See http://sokobano.de/wiki/index.php?title=Sok_format for more information
     */
    void parseSOK( std::ifstream& file, std::map<std::string, Level*>& levelMap );

    /*!
     * @brief Registers a level to a level map
     */
    void registerLevel( Level* level, std::string& levelName, std::map<std::string, Level*>& levelMap );

};

} // namespace Sokoban

#endif // __SOKOBAN_CORE_COLLECTION_PARSER_HPP__
