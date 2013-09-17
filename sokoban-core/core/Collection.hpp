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

#include <core/Export.hpp>

#include <vector>
#include <string>

namespace Sokoban {

// --------------------------------------------------------------
// forward declarations

class Level;

/*!
 * @brief Holds a collection of levels which can be read from a file
 */
class SOKOBAN_CORE_API Collection
{
public:

    typedef std::vector<Level*>::iterator iterator;

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
     *
     * Unloads everything (this calls the deinitialise method)
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
     *
     * This can be called when switching collections to save memory.
     * While it is not necessary to do so, it is recommended, because progress
     * is only saved once this is called. You can also keep all of
     * the levels loaded for later usage, but you run the risk of something
     * going wrong and losing all progress.
     *
     * @note You may initialise and deinitialise as many times as you like.
     * The file is parsed again whenever initialise is called, and saved whenever
     * deinitialise is called.
     */
    void deinitialise( void );

    /*!
     * @brief Sets the name of this collection
     *
     * The name is read from the file when initialise is called, but
     * can be changed afterwards with this method. If you change the name,
     * the new name will be written to the file when deinitialise is called.
     *
     * @param name The name to set
     */
    void setName( const std::string& name );

    /*!
     * @brief Gets the name of this collection
     *
     * The name is read from the file when initialise is called, and can be
     * retrieved with this method.
     *
     * @return The name of the collection
     */
    std::string getName( void ) const;

    /*!
     * @brief Enables compression of exported files
     *
     * Depending on what exporter is selected, a corresponding
     * compression algorithm is applied.
     *
     * @note Default is <b>disabled</b>
     */
    void enableCompression( void );

    /*!
     * @brief Disables compression of exported files
     *
     * @note Default is <b>disabled</b>
     */
    void disableCompression( void );

    /*!
     * @brief Writes a list of level names into an std::vector<std::string> object
     *
     * This is useful for letting the end-user know what level he/she/it is playing,
     * and can also be used to get more information from a specific level (such as tile data)
     *
     * @param vs The std::vector<std::string> to write to.
     * @note The vector-string is <b>cleared</b> when calling this.
     */
    void getLevelNames( std::vector<std::string>& vs );



private:

    std::string m_FileName;
    std::string m_CollectionName;
    std::vector<Level*> m_Levels;
    bool m_EnableCompression;
    bool m_IsInitialised;
};

} // namespace Sokoban

#endif // __SOKOBAN_CORE_COLLECTION_HPP__
