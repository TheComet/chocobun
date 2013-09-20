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
// Collection Parser
// --------------------------------------------------------------

#ifndef __CHOCOBUN_CORE_COLLECTION_PARSER_HPP__
#define __CHOCOBUN_CORE_COLLECTION_PARSER_HPP__

// --------------------------------------------------------------
// include files

#include <vector>
#include <string>

namespace Chocobun {

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
	 * @brief List of file formats that are supported for export
	 */
    enum FILE_FORMAT
	{
		FORMAT_SOK,
		FORMAT_SLC
	};

    /*!
     * @brief Constructor
     */
    CollectionParser( void );

    /*!
     * @brief Destructor
     */
    ~CollectionParser( void );

    /*!
     * @brief Parses a collection file and writes into a vector of levels
     *
     * @param fileName The name of the file to parse
     * @param levels An std::vector of levels to write to
     * @return Returns the name of the collection (if any), otherwise the string
     * is empty
     */
    std::string parse( const std::string& fileName, std::vector<Level*>& levels );

    /*!
     * @brief Saves a collection to a file
     *
     * Will export using the .SOK format, regardless of input format
     *
     * @param fileName The file name to save to
     * @param levels An std::vector of levels to save
     * @param enableCompression
     */
    void save( const std::string& collectionName, const std::string& fileName, std::vector<Level*>& levels, bool enableCompression = false );

	/*!
	 * @brief Sets the export file format to be used for every future save
	 *
	 * @param fileFormat The file format
	 */
    void setFileFormat( FILE_FORMAT fileFormat );

	/*!
	 * @brief Gets the set export file format being used
	 *
	 * @return The export format
	 */
    FILE_FORMAT getFileFormat( void );

private:

    FILE_FORMAT m_fileFormat;

};

} // namespace Chocobun

#endif // __CHOCOBUN_CORE_COLLECTION_PARSER_HPP__
