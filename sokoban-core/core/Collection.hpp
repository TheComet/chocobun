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
// Collection
// --------------------------------------------------------------

#ifndef __SOKOBAN_CORE_COLLECTION_HPP__
#define __SOKOBAN_CORE_COLLECTION_HPP__

// --------------------------------------------------------------
// include files

#include <vector>
#include <string>

namespace Sokoban {

// --------------------------------------------------------------
// forward declarations

class Level;

/*!
 * @brief Holds a collection of levels which can be read from a file
 */
class Collection
{
public:

    /*!
     * @brief Constructs a collection from a given file
     *
     * @param fileName The file to read the collections from
     *
     * @remarks This does not actually load the file, it only stores
     * the file name internally until the initialise method is called
     */
    Collection( const std::string& fileName );

    /*!
     * @brief Destructor
     */
    ~Collection( void );

    /*!
     * @brief Initialises the collection
     *
     * Will parse the file specified in the constructor and load all
     * levels into memory
     */
    void initialise( void );

    /*!
     * @brief De-initialises the collection, freeing up all memory
     */
    void deinitialise( void );

    /*!
     * @brief Sets the name of this collection
     *
     * @param name The name to set
     */
    void setName( const std::string& name );

private:

    std::string m_FileName;
    std::string m_CollectionName;
    std::vector<Level*> m_Levels;
};

} // namespace Sokoban

#endif // __SOKOBAN_CORE_COLLECTION_HPP__
