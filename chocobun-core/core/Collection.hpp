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

    std::vector<Level*>& getLevels( void ) { return m_Levels; }

    /*!
     * @brief Default constructor
     */
    Collection( void );

    /*!
     * @brief Copy Constructor
     */
    Collection( const Collection& that );

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
    void load( const std::string& fileName );

    /*!
     * @brief Unloads the collection, saving it to disk and freeing up all memory
     *
     * This can be called when switching collections to save memory.
     * While it is not necessary to do so, it is recommended, because progress
     * is only saved once this is called. You can also keep all of
     * the levels loaded for later usage, but you run the risk of something
     * going wrong and losing all progress.
     *
     * @note You may @a load and @a unload as many times as you like.
     * The file is parsed again whenever @a load is called, and saved whenever
     * @a unload is called.
     */
    void unload( void );

    /*!
     * @brief Sets the name of this collection
     *
     * The name is read from the file when initialise is called, but
     * can be changed afterwards with this method. If you change the name,
     * the new name will be written to the file when @a unload is called.
     *
     * @param name The name to give to this collection
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
    const std::string& getName( void ) const;

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
     * @brief Checks if compression is enabled or not
     * @return Returns true if compression is enabled, false if not
     */
    bool isCompressionEnabled( void ) const;

    /*!
     * @brief Sets the export file format to be used for every future save
     *
     * @param fileFormat The file format
     */
    void setFileFormat( CollectionParser::FILE_FORMAT fileFormat );

    /*!
     * @brief Gets the set export file format being used
     *
     * @return The export format
     */
    CollectionParser::FILE_FORMAT getFileFormat( void );

    /*!
     * @brief Adds a new, empty level to the collection
     */
    Level* addLevel( void );

    /*!
     * @brief Removes and destroys a level from the collection
     */
    void removeLevel( Level* lvl );

    /*!
     * @brief Removes and destroys a level from the collection
     */
    void removeLevel( const std::string& levelName );

    /*!
     * @brief Generates name for the level if the passed string is empty
     */
    void generateLevelName( std::string& name );

    /*!
     * @brief Returns the pointer to the specified level object
     */
    Level* getLevelPtr( const std::string& levelName );

    /*!
     * @brief Returns a reference to the specified level object
     */
    Level& getLevel( const std::string& levelName );

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

    /*!
     * @brief Streams all level names to an output stream object
     *
     * This is usefull for letting the end-user know what level he/she/it is playing,
     * and can also be used to get more information from a specific level (such as tile data)
     *
     * @param stream An output stream object
     */
    void streamLevelNames( std::ostream& stream );

    /*!
     * @brief Selects a level so it is ready to play
     *
     * When a level is selected, everything about the level can be retrieved through
     * "getActiveLevel..." methods. Internally, the only thing that's happening is
     * a pointer is set to point to the active level.
     *
     * @param levelName The name of the level
     * @note You can retrieve a list of names with <b>getLevelNames</b>
     * @return If the active level doesn't exist, false is returned, otherwise true is returned.
     */
    void setActiveLevel( const std::string& levelName );

    /*!
     * @brief Checks if a level is selected as active or not
     *
     * @return True if a level is selected as active, false if otherwise
     */
    bool hasActiveLevel( void );

    /*!
     * @brief Returns all tiles of the active level
     *
     * All tiles of the active level are contained within a dynamic 2-dimensional
     * array or chars (std::vector< std::vector<char> >).
     *
     * <b>Valid tiles are:</b>
     * - # Wall
     * - @ Pusher
     * - + Pusher on goal square
     * - $ Box
     * - * Box on goal square
     * - . Goal square
     * -   Floor (space)
     * - _ Floor
     *
     * @note If the tiles could not be retrieved, an empty array is returned.
     *
     * @exception Throws an std::exception if an active level wasn't selected
     * before calling this method
     *
     * @param vvs A 2-dimensional array of chars to write the level data of the active level to
     */
    void getTileData( LevelArray_t& tiles ) const;

    /*!
     * @brief Streams all tiles of the active level to an output stream object
     *
     * If the streaming fails, the stream object will be unchanged.
     *
     * @param stream The output stream object to stream to
     */
    void streamTileData( std::ostream& stream );

    /*!
     * @brief Retrieves a specific tile from the active level
     *
     *
     * <b>Valid tiles are:</b>
     * - # Wall
     * - @ Pusher
     * - + Pusher on goal square
     * - $ Box
     * - * Box on goal square
     * - . Goal square
     * -   Floor (space)
     * - _ Floor
     *
     * @param x The X-coordinate of the tile to retrieve
     * @param y The Y-coordinate of the tile to retrieve
     * @return Returns the tile at the specified locations. If the tile couldn't be
     * retrieved, a null character ('\0') is returned.
     */
    char getTile( const Uint32 x, const Uint32 y );

    /*!
     * @brief Sets a specific tile on the active level
     *
     * <b>Valid tiles are:</b>
     * - # Wall
     * - @ Pusher
     * - + Pusher on goal square
     * - $ Box
     * - * Box on goal square
     * - . Goal square
     * -   Floor (space)
     * - _ Floor
     *
     * @param x The X-coordinate of the tile to set
     * @param y The Y-coordinate of the tile to set
     * @param tile The tile to set it to
     */
    void setTile( const Uint32 x, const Uint32 y, const char tile );

    /*!
     * @brief Returns the X-size of the active level
     *
     * @return The X-size of the active level
     */
    Uint32 getSizeX( void ) const;

    /*!
     * @brief Returns the Y-size of the active level
     *
     * @return The Y-size of the active level
     */
    Uint32 getSizeY( void ) const;

    /*!
     * @brief Returns the maximum X-size of the largest level in the collection
     */
    Uint32 getMaxSizeX( void );

    /*!
     * @brief Returns the maximum Y-size of the largest level in the collection
     */
    Uint32 getMaxSizeY( void );

    /*!
     * @brief Adds a level listener
     * Registers an object inheriting from LevelListener so it can receive level events
     * @param listener The object to register
     * @return Returns true if successfully registered, false if otherwise
     */
    void addLevelListener( LevelListener* listener );

    /*!
     * @brief Removes a level listener
     * @param listener The object to unregister
     * @return Returns true if successfully unregistered, false if otherwise
     */
    void removeLevelListener( LevelListener* listener );

    /*!
     * @brief Moves the player up in the active level
     *
     * The tile data is internally updated and can be retrieved with
     * either <b>getTileData</b>, <b>streamTileData</b> or <b>getTile</b>
     *
     * If the move is not possible, this method will silently fail
     */
    void moveUp( void );

    /*!
     * @brief Moves the player down in the active level
     */
    void moveDown( void );

    /*!
     * @brief Moves the player left in the active level
     */
    void moveLeft( void );

    /*!
     * @brief Moves the player right in the active level
     */
    void moveRight( void );

    /*!
     * @brief Undoes a move in the active level if any
     */
    void undo( void );

    /*!
     * @brief Redoes a move in the active level if any
     */
    void redo( void );

    /*!
     * @brief Resets the active level to its initial state and erases all undo data
     */
    void reset( void );

    /*!
     * @brief Overload assignment operator
     */
    Collection& operator=( const Collection& that );

private:

    std::string m_FileName;
    std::string m_CollectionName;
    std::vector<Level*> m_Levels;
    std::vector<LevelListener*> m_LevelListeners;
    Level* m_ActiveLevel;
    bool m_EnableCompression;
    bool m_IsLoaded;

    CollectionParser::FILE_FORMAT m_FileFormat;
};

} // namespace Chocobun

#endif // __CHOCOBUN_CORE_COLLECTION_HPP__
