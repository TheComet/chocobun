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
// Universal SOK parser
// --------------------------------------------------------------

#ifndef __SOKOBAN_CORE_COLLECTION_PARSER_SOK_HPP__
#define __SOKOBAN_CORE_COLLECTION_PARSER_SOK_HPP__

// --------------------------------------------------------------
// include files

#include <core/CollectionParserBase.hpp>

namespace Sokoban {

/*!
 * @brief Universal .SOK format parser
 *
 * See http://sokobano.de/wiki/index.php?title=Sok_format for more information
 */
class CollectionParserSOK :
    public CollectionParserBase
{
public:

    /*!
     * @brief Constructor
     */
    CollectionParserSOK( void );

    /*!
     * @brief Destructor
     */
    ~CollectionParserSOK( void );

    /*!
     * @brief Parses a .SOK file
     *
     * See http://sokobano.de/wiki/index.php?title=Sok_format for more information
     *
     * @param file An open file object to read from
     * @param levelMap An std::map of levels to write to
     * @return Returns the name of the collection (if any), otherwise the string
     * is empty
     */
    std::string parse( std::ifstream& file, std::map<std::string, Level*>& levelMap );

    /*!
     * @brief Universal .SOK format exporter
     *
     * See http://sokobano.de/wiki/index.php?title=Sok_format for more information
     *
     * @param file An open file object to write data to
     * @param levelMap An std::map of levels to read from
     */
    void save( std::ofstream& file, std::map<std::string, Level*>& levelMap );

private:

    /*!
     * @brief Returns true if the string is level data
     */
    bool isLevelData( const std::string& str );

    /*!
     * @brief Extracts key value pairs and returns true or false if successful
     *
     * @param str The string to search for key-value pairs
     * @param key Output string where the key is written to
     * @param value Output string where the value is written to
     * @return True if a key-value pair was found, false if otherwise
     */
    bool getKeyValuePair( const std::string& str, std::string& key, std::string& value );

};

} // namespace Sokoban

#endif // __SOKOBAN_CORE_COLLECTION_PARSER_SOK_HPP__
