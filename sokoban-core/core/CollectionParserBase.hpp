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
// Base class for all collection parsers
// --------------------------------------------------------------

// --------------------------------------------------------------
// include files

#include <string>
#include <vector>

namespace Sokoban {

// --------------------------------------------------------------
// forward declarations
class Level;

/*!
 * @brief Base class for all collection parsers
 */
class CollectionParserBase
{
public:

    /*!
     * @brief Constructor
     */
    CollectionParserBase( void );

    /*!
     * @brief Destructor
     */
    virtual ~CollectionParserBase( void );

    /*!
     * @brief Parses and loads all levels into a vector of Level objects
     *
     * This method is pure virtual and must be implemented by the inheriting class
     */
    virtual std::string parse( std::ifstream& file, std::vector<Level*>& levels ) = 0;

    /*!
     * @brief Saves a vector of level objects to a file
     *
     * This method is pure virtual and must be implemented by the inheriting class
     */
    virtual void save( const std::string& collectionName, std::ofstream& file, std::vector<Level*>& levels ) = 0;

    /*!
     * @brief Enables compression of exported files
     *
     * Depending on what exporter is selected, a corresponding
     * compression algorithm is applied.
     *
     * @note Default is <b>disabled</b>
     */
    virtual void enableCompression( void );

    /*!
     * @brief Disables compression of exported files
     *
     * @note Default is <b>disabled</b>
     */
    virtual void disableCompression( void );

protected:

    /*!
     * @brief Registers a level to a level vector
     */
    void registerLevel( Level* level, std::string& levelName, std::vector<Level*>& levels );

};

} // namespace Sokoban
