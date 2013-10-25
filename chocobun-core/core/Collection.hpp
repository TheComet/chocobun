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
// Collection.hpp
// --------------------------------------------------------------

#ifndef __CHOCOBUN_CORE_COLLECTION_HPP__
#define __CHOCOBUN_CORE_COLLECTION_HPP__

// --------------------------------------------------------------
// include files

#include <core/Typedefs.hpp>
#include <core/Export.hpp>
#include <core/LevelListener.hpp>
#include <core/CollectionParser.hpp>
#include <vector>
#include <string>

namespace Chocobun {

// --------------------------------------------------------------
// forward declarations

class Level;

/*!
 * @brief Holds a collection of levels which can be read from a file
 */
class CHOCOBUN_CORE_API Collection :
    public LevelListener
{
public:

    /*!
     * @brief Default constructor
     */
    Collection( void );

    /*!
     * @brief Copy Constructor
     * Will perform a deep copy on all containing levels
     */
    Collection( const Collection& that );

    /*!
     * @brief Destructor
     * Unloads everything (this calls @a unload)
     */
    ~Collection( void );

    /*!
     * @brief Sets the name of this collection
     * The name of the collection is exported to the save file
     * @param name The name to give to this collection
     */
    void setCollectionName( const std::string& name );

    /*!
     * @brief Gets the current name of this collection
     * @return The name
     */
    const std::string& getCollectionName( void ) const;

    /*!
     * @brief Adds a new, empty level to the collection
     * The level is added to a list internally for later reference. If you wish
     * to perform further operations on the specific level, the pointer to it
     * is returned, so you could do something like the following:
     * @code
     * Collection myCollection();
     * myCollection.addLevel()->setLevelName( "myLevel" );
     * @endcode
     * You can get the level pointer at any time again with the methods
     * @a getLevelPtr and @a getLevel.
     * @return A pointer to the created level object
     */
    Level* addLevel( void );

    /*!
     * @brief Removes and destroys a level from the collection by pointer
     * The level is permanently removed from the collection
     * @param lvl Pointer to the level to remove
     */
    void removeLevel( Level* lvl );

    /*!
     * @brief Removes and destroys a level from the collection by name
     * The level is permanently removed from the collection
     * @param levelName The name of the level to remove
     */
    void removeLevel( const std::string& levelName );

    /*!
     * @brief Returns the number of levels currently registered in the collection
     * @return The number of levels
     */
    std::size_t getLevelCount( void ) const;

    /*!
     * @brief Returns a pointer to a level object specified by its name
     * This can be used to manipulate the level object
     * @exception Throws a Chocobun::Exception if the level name was not found
     * in the collection
     * @param levelName The name of the level to retrieve
     * @return The pointer to the level
     */
    Level* getLevelPtr( const std::string& levelName ) const;

    /*!
     * @brief Returns a pointer to a level object specified by its index
     * The index to a level ranges from 0 to @a getLevelCount
     * @exception Throws a Chocobun::Exception if the index is out of range
     * @param ID The index of the level to retrieve
     * @return The pointer to the level
     */
    Level* getLevelPtr( const std::size_t& ID ) const;

    /*!
     * @brief Returns a reference to a level object specified by its name
     * This can be used to manipulate the level object
     * @exception Throws a Chocobun::Exception if the level name was not found
     * in the collection
     * @param levelName The name of the leveel to retrieve
     * @return The reference to the level
     */
    Level& getLevel( const std::string& levelName ) const;

    /*!
     * @brief Returns a reference to a level object specified by its index
     * The index to a level ranges from 0 to @a getLevelCount
     * @exception Throws a Chocobun::Exception if the index is out of range
     * @param ID The index of the level to retrieve
     * @return The reference to the level
     */
    Level& getLevel( const std::size_t& ID ) const;

    /*!
     * @brief Creates a list of level names and returns it
     */
    std::vector<std::string> getLevelNames( void ) const;

    void streamLevelNames( std::ostream& stream ) const;

    void selectFirstLevel( void );

    void selectLastLevel( void );

    bool selectNextLevel( void );

    bool selectPreviousLevel( void );

    void setActiveLevel( const std::string& levelName );

    bool hasActiveLevel( void );

    void generateLevelName( std::string& currentName );

/*
    void load( const std::string& fileName );

    void save( const std::string& fileFormat );

    void unload( void );

    const std::string& getName( void ) const;

    void enableCompression( void );

    void disableCompression( void );

    bool isCompressionEnabled( void ) const;

    level_iterator level_begin( void );

    level_iterator level_end( void );

    const const_level_iterator level_begin( void ) const;

    const const_level_iterator level_end( void ) const;

    Uint32 getMaxSizeX( void );

    Uint32 getMaxSizeY( void );

    void addLevelListener( LevelListener* listener );

    void removeLevelListener( LevelListener* listener );

    void moveUp( void );

    void moveDown( void );

    void moveLeft( void );

    void moveRight( void );

    void undo( void );

    void redo( void );

    void reset( void );

    void onSetTile( const std::size_t& x, const std::size_t& y, const char& tile );

    void onMoveTile( const std::size_t& oldX, const std::size_t& oldY, const std::size_t& newX, const std::size_t& newY );
*/
    Collection& operator=( const Collection& that );

private:

    std::vector<Level*> m_Levels;
    std::string m_CollectionName;
    std::size_t m_ActiveLevel;
};

} // namespace Chocobun

#endif // __CHOCOBUN_CORE_COLLECTION_HPP__
