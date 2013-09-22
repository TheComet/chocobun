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
// Collection
// --------------------------------------------------------------

#ifndef __CHOCOBUN_CORE_COLLECTION_HPP__
#define __CHOCOBUN_CORE_COLLECTION_HPP__

// --------------------------------------------------------------
// include files

#include <core/Export.hpp>
#include <core/CollectionParser.hpp>

#include <vector>
#include <string>

namespace Chocobun {

// --------------------------------------------------------------
// forward declarations

class Level;
class LevelListener;

/*!
 * @brief Holds a collection of levels which can be read from a file
 */
class CHOCOBUN_CORE_API Collection
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
     * @brief De-initialises the collection, saving it to disk and freeing up all memory
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
    bool setActiveLevel( const std::string& levelName );

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
     * @return Returns a 2-dimensional array of chars containing level data of the active level
     */
    const std::vector< std::vector<char> >& getTileData( void ) const;

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
     * @return Returns true if the tile was successfully set, false if otherwise
     */
    bool setTile( const Uint32 x, const Uint32 y, const char tile );

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
     * @brief Validates the active level
     *
     * Will perform various checks to see if the level is valid. This includes:
     * - Only one player can exist on a level
     * - All boxes can be reached by the player
     * - All boxes which can't be reached by the player are placed on goal squares
     * - The level is closed off entirely by a wall
     *
     * @note It is essential to call this method before using the level for game play.
     * This method also 'finalises' the level by performing some internal setup on the
     * provided tile data
     *
     * If there is no active level selected, false is returned.
     *
     * @return If any of these fail, false is returned. If the level is considered valid, true is returned.
     */
    bool validateLevel( void ) const;

    /*!
     * @brief Adds a level listener
     * Registers an object inheriting from LevelListener so it can receive level events
     * @param listener The object to register
     * @return Returns true if successfully registered, false if otherwise
     */
    bool addLevelListener( LevelListener* listener );

    /*!
     * @brief Removes a level listener
     * @param listener The object to unregister
     * @return Returns true if successfully unregistered, false if otherwise
     */
    bool removeLevelListener( LevelListener* listener );

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

private:

    std::string m_FileName;
    std::string m_CollectionName;
    std::vector<Level*> m_Levels;
    std::vector<LevelListener*> m_LevelListeners;
    Level* m_ActiveLevel;
    bool m_EnableCompression;
    bool m_IsInitialised;

    CollectionParser::FILE_FORMAT m_FileFormat;
};

} // namespace Chocobun

#endif // __CHOCOBUN_CORE_COLLECTION_HPP__
