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
// Level
// --------------------------------------------------------------

#ifndef __CHOCOBUN_CORE_LEVEL_HPP__
#define __CHOCOBUN_CORE_LEVEL_HPP__

// --------------------------------------------------------------
// include files

#include <core/Config.hpp>

#include <string>
#include <vector>
#include <map>

#include <iostream>

namespace Chocobun {

class LevelListener;

/*!
 * @brief Holds information of a loaded level
 */
class Level
{
public:

    static const std::string validTiles;

    typedef std::map<std::string, Level*>::iterator metaDataIterator;

    /*!
     * @brief Default Constructor
     */
    Level( void );

    /*!
     * @brief Destructor
     */
    ~Level( void );

    /*!
     * @brief Adds meta data to the level
     *
     * Meta data is very loosely defined in the file format specifications,
     * therefore this method allows any key-value pair to be registered.
     *
     * Supported internal keys are
     * - Collection
     * - Author
     *
     * @note Keys are case sensitive and should be converted to lower case
     * before adding the meta data.
     *
     * @exception Chocobun::Exception If the key already exists
     *
     * @param key The key of the entry (used to get the data back later on)
     * @param value The value of the entry (can by any text string)
     */
    void addMetaData( const std::string& key, const std::string& value );

    /*!
     * @brief Retrieves meta data of the level
     *
     * @exception Chocobun::Exception if the key was not found
     *
     * @param key The key of the entry to search for
     * @return The value tied to the key
     */
    const std::string& getMetaData( const std::string& key );

    /*!
     * @brief Formats and streams all meta data to a stream object
     *
     * This is used when saving the level's meta data
     *
     * @param stream The stream object to stream to
     */
    void streamAllMetaData( std::ostream& stream );

    /*!
     * @brief Adds Header data and other text for this level
     *
     * This is used later on when the file is saved to disk again,
     * so headers that would not normally be loaded are preserved
     *
     * @param header Header to add
     */
    void addHeaderData( const std::string& header );

    /*!
     * @brief Removes header data from this level
     *
     * This is called when a level name is discovered. Because
     * there can be multiple passes of delay before a level name can
     * be confirmed, it usually occurs that it has been added as a
     * Header first. This will remove it again so it isn't exported twice.
     *
     * @param header The Header string to remove
     */
    void removeHeaderData( const std::string& header );

    /*!
     * @brief Streams all header data to a stream object
     *
     * This is used to save the header data of a level
     *
     * @param stream The stream object to stream to
     */
    void streamAllHeaderData( std::ostream& stream );

    /*!
     * @brief Inserts a tile into the level at the given coordinate
     *
     * Internally the map array is resized accordingly so it remains square.
     * <b>Valid tile characters are:</b>
     * - # Wall
     * - @ Pusher
     * - + Pusher on goal square
     * - $ Box
     * - * Box on goal square
     * - . Goal square
     * -   Floor (space)
     * - _ Floor
     *
     * @exception Chocobun::Exception if an invalid character is passed
     *
     * @param x The X coordinate for the tile to insert
     * @param y The Y coordinate for the tile to insert
     * @param tile The type of tile
     */
    void insertTile( const Chocobun::Uint32& x, const Chocobun::Uint32& y, const char& tile );

    /*!
     * @brief Inserts a whole line instead of a single tile
     *
     * Internally the map array is resized accordingly so it remains square.
     * <b>Valid tile characters are:</b>
     * - # Wall
     * - @ Pusher
     * - + Pusher on goal square
     * - $ Box
     * - * Box on goal square
     * - . Goal square
     * -   Floor (space)
     * - _ Floor
     *
     * @exception Chocobun::Exception if an invalid character is passed
     *
     * @param y The Y coordinate for the tile line to insert
     * @param tiles The line of tiles to insert
     */
    void insertTileLine( const Chocobun::Uint32& y, const std::string& tiles );

    /*!
     * @brief Streams all current tile data to a stream object
     *
     * This can be used to retrieve all of the tiles to update
     * the screen when a move is made
     *
     * @param stream The output stream object to stream to
     * @param newLine If set to true (default), new line breaks are inserted.
     * Otherwise, "|" are inserted (for RLE compression)
     */
    void streamAllTileData( std::ostream& stream, bool newLine = true );

    /*!
     * @brief Gets the array of current tile data
     *
     * @return Returns a 2-dimensional array of chars containing tile data
     */
    const std::vector< std::vector<char> >& getTileData( void ) const;

    /*!
     * @brief Streams the tile data of this level in its initial state
     *
     * Retrieves all of the tiles as they initially were. This is best used
     * to save levels to a file.
     *
     * @param stream The output stream object to stream to
     * @param newLine If set to true (default), new line breaks are insterted.
     * Otherwise, "|" are inserted (for RLE compression)
     */
    void streamInitialTileData( std::ostream& stream, bool newLine = true );

    /*!
     * @brief Gets a single tile from the level
     *
     * Will retrieve the tile data specified by the x and y parameters
     *
     * @param x The X-coordinate of the tile
     * @param y The Y-coordinate of the tile
     * @return Returns the tile at the specified coordinates. If the tile couldn't
     * be retrieved, a null character ('\0') is returned.
     */
    char getTile( Uint32 x, Uint32 y ) const;

    /*!
     * @brief Sets the specified tile and informs all listeners
     *
     * All listeners are informed about the tile change when this is called.
     *
     * @param x The x-coordinate of the tile
     * @param y The y-coordinate of the tile
     * @param tile The tile to set it to
     */
    bool setTile( const Uint32& x, const Uint32& y, const char& tile );

    /*!
     * @brief Returns the X-size of the level
     *
     * @return The X-size of the level
     */
    Uint32 getSizeX( void ) const;

    /*!
     * @brief Returns the Y-size of the level
     *
     * @return The Y-size of the level
     */
    Uint32 getSizeY( void ) const;

    /*!
     * @brief Adds level notes to this level
     *
     * @param note The notes string to add
     */
    void addLevelNote( const std::string& note);

    /*!
     * @brief Removes level notes from this level
     *
     * @param note The note to search for and remove
     */
    void removeLevelNote( const std::string& note );

    /*!
     * @brief Streams all notes to a stream object
     *
     * This is used to save the level data to a file
     *
     * @param stream The stream object to stream to
     */
    void streamAllNotes( std::ostream& stream );

    /*!
     * @brief Sets the name of the level
     */
    void setLevelName( const std::string& name );

    /*!
     * @brief Gets the name of the level
     */
    std::string getLevelName( void ) const;

    /*!
     * @brief Returns all undo/redo data in the form of a string
     *
     * This is used to save undo/redo data to a file so it can be
     * imported again.
     *
     * @return The undo/redo data string
     */
    std::string exportUndoData( void );

    /*!
     * @brief Imports an undo/redo data string previously exported
     *
     * @param undoData The undo/redo data string
     */
    void importUndoData( const std::string& undoData );

    /*!
     * @brief Validates the level
     *
     * Will perform various checks to see if the level is valid. This includes:
     * - Only one player can exist on a level
     * - All boxes can be reached by the player
     * - All boxes which can't be reached by the player are placed on goal squares
     * - The level is closed off entirely by a wall
     *
     * @note It is essential to call this method before using the level for game play.
     * This method also 'finalises' the level by performing some internal setup on the
     * provided tile data.
     *
     * @return If any of these fail, false is returned. If the level is considered valid, true is returned.
     */
    bool validateLevel( void );

    /*!
     * @brief Moves the player up by one tile
     * @note If the move is not possible, this method will silently fail
     */
    void moveUp( void );

    /*!
     * @brief Moves the player down by one tile
     * @note If the move is not possible, this method will silently fail
     */
    void moveDown( void );

    /*!
     * @brief Moves the player left by one tile
     * @note If the move is not possible, this method will silently fail
     */
    void moveLeft( void );

    /*!
     * @brief Moves the player right by one tile
     * @note If the move is not possible, this method will silently fail
     */
    void moveRight( void );

    /*!
     * @brief Undoes the last move
     * @return Returns false if there is no more undo data, otherwise true is returned
     */
    bool undo( void );

    /*!
     * @brief Redoes a move
	 * @return Returns false if there is no more data to redo, otherwise true is returned
     */
    bool redo( void );

    /*!
     * @brief Resets the level to its initial state
     */
    void reset( void );

    /*!
     * @brief Checks if undo data exists or not
     * @return Returns true if undo data exists, false if it doesn't
     */
    bool undoDataExists( void );

    /*!
     * @brief Checks if redo data exists or not
     * @return Returns true if redo data exists, false if it doesn't
     */
    bool redoDataExists( void );

    /*!
     * @brief Registers a level listener
     *
     * @param listener A pointer to an object inheriting from LevelListener
     * @return Returns true if the listener was registered successfully,
     * false if otherwise
     */
    bool addListener( LevelListener* listener );

    /*!
     * @brief Unregisters a level listener
     * @param listener A pointer to an object inheriting from LevelListener
     * @return Returns true if the listener was unregistered successfully,
     * false if otherwise
     */
    bool removeListener( LevelListener* listener );

private:

    /*!
     * @brief Moves the player and updates all tiles
     *
     * @param direction The direction to move the player, can be either
     * u, d, l, r, or U, D, L, R (upper case or lower case - it does the same thing)
     * @param updateUndoData Set this to false if this move should not be
     * registered as a move that can be undone
     * @return Returns true if the move was successful, false if otherwise
     */
    bool movePlayer( char direction, bool updateUndoData = true );

    /*!
     * @brief Dispatches the set tile event
     * This occurs whenever a tile is changed
     */
    void dispatchSetTile( const Uint32& x, const Uint32& y, const char& tile );

    std::map<std::string, std::string> m_MetaData;
    std::vector< std::vector<char> > m_LevelArray;
    std::vector<std::string> m_HeaderData;
    std::vector<std::string> m_Notes;
    std::vector<char> m_UndoData;
    std::string m_LevelName;
    std::vector<LevelListener*> m_LevelListeners;

    Uint32 m_PlayerX;
    Uint32 m_PlayerY;
    std::size_t m_UndoDataIndex;

    bool m_IsLevelValid;
};

} // namespace Chocobun

#endif // __CHOCOBUN_CORE_LEVEL_HPP__
