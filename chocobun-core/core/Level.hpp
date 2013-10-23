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
// Level.hpp
// --------------------------------------------------------------

#ifndef __CHOCOBUN_CORE_LEVEL_HPP__
#define __CHOCOBUN_CORE_LEVEL_HPP__

// --------------------------------------------------------------
// include files

#include <core/Config.hpp>
#include <core/TileField.hpp>

#include <string>
#include <vector>
#include <map>

#include <iostream>

namespace Chocobun {

// --------------------------------------------------------------
// forward declarations

class LevelListener;
class TileField;

/*!
 * @brief Holds information of a loaded level
 */
class Level
{
public:

    /*!
     * @brief Default Constructor
     */
    Level( void );

    /*!
     * @brief Copy constructor
     */
    Level( const Level& that );

    /*!
     * @brief Destructor
     */
    ~Level( void );

    TileField& getActiveTileField( void ) { return m_LevelArray; }
    TileField* getActiveTileFieldPtr( void ) { return &m_LevelArray; }

    TileField& getInitialTileField( void ) { return m_InitialLevelArray; }
    TileField* getInitialTileFieldPtr( void ) { return &m_InitialLevelArray; }

    /*!
     * @brief Adds meta data to the level
     * Meta data is very loosely defined in the file format specifications,
     * therefore this method allows any key-value pair to be registered.
     *
     * Supported internal keys are
     * - Collection
     * - Author
     * @note Keys are case sensitive
     * @exception Chocobun::Exception If the key already exists
     * @param key The key of the entry (used to get the data back later on)
     * @param value The value of the entry (can by any text string)
     */
    void addMetaData( const std::string& key, const std::string& value );

    /*!
     * @brief Retrieves meta data from the level
     * @exception Chocobun::Exception if the key was not found
     * @param key The key of the entry to search for
     * @return The value tied to the key
     */
    const std::string& getMetaData( const std::string& key );

    /*!
     * @brief Formats and streams all meta data to a stream object
     * This is used when saving the level's meta data. Key and value
     * are separated by a colon.
     * @param stream The stream object to stream to
     */
    void streamAllMetaData( std::ostream& stream );

    /*!
     * @brief Adds Header data and other text for this level
     * This is used later on when the file is saved to disk again,
     * so headers that would not normally be loaded are preserved
     * @param header Header to add
     */
    void addHeaderData( const std::string& header );

    /*!
     * @brief Removes header data from this level
     * This is called when a level name is discovered. Because
     * there can be multiple passes of delay before a level name can
     * be confirmed, it usually occurs that it has been added as a
     * Header first. This will remove it again so it isn't exported twice.
     * @param header The Header string to remove
     */
    void removeHeaderData( const std::string& header );

    /*!
     * @brief Streams all header data to a stream object
     * This is used to save the header data of a level
     * @param stream The stream object to stream to
     */
    void streamAllHeaderData( std::ostream& stream );

    /*!
     * @brief Adds level notes to this level
     * @param note The notes string to add
     */
    void addLevelNote( const std::string& note);

    /*!
     * @brief Removes level notes from this level
     * @note If the level note doesn't exist, this method will silently fail.
     * @param note The note to search for and remove
     */
    void removeLevelNote( const std::string& note );

    /*!
     * @brief Streams all notes to a stream object
     * This is used to save the level data to a file.
     * @param stream The stream object to stream to
     */
    void streamAllNotes( std::ostream& stream );

    /*!
     * @brief Sets the name of the level
     * @note If the level name has already been set, this will overwrite it.
     */
    void setLevelName( const std::string& name );

    /*!
     * @brief Gets the name of the level
     */
    const std::string& getLevelName( void ) const;

    /*!
     * @brief Returns all undo/redo data in the form of a string
     * This is used to save undo/redo data to a file so it can be
     * imported again.
     * @return The undo/redo data string
     */
    std::string exportUndoData( void );

    /*!
     * @brief Imports an undo/redo data string previously exported
     * Unfortunately, some sokoban level formats allow undo data to be imported
     * before the tiles actually exist, so the undo data cannot immediately be
     * applied to the level. (see issue #15)
     * Therefore, the undo data is only evaluated and saved here, but still
     * needs to be applied with @a applyUndoData.
     * @exception Chocobun::Exception if the input string is invalid.
     * @param undoData The undo/redo data string
     */
    void importUndoData( const std::string& undoData );

    /*!
     * @brief Applies any imported undo data to the level
     * In the case of there being no undo data, this method will simply
     * do nothing.
     * @note This will reset the level, even if no undo data exists
     * @exception If the level is not valid, a Chocobun::Exception is thrown
     */
    void applyUndoData( void );

    /*!
     * @brief Validates the level
     *
     * Will perform various checks to see if the level is valid. This includes:
     * - Only one player can exist on a level
     * - All boxes can be reached by the player
     * - All boxes which can't be reached by the player are placed on goal squares
     * - The level is closed off entirely by a wall
     * // TODO implement these points listed above
     *
     * @note It is essential to call this method before using the level for game play.
     * This method also 'finalises' the level by performing some internal setup on the
     * provided tile data. This includes:
     * - Player x,y coordinates are set
     * - Level is reset and undo data is applied
     * @exception If the level is invalid, a Chocobun::Exception is thrown with
     * a detailed description of what went wrong.
     */
    void validateLevel( void );

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
     * @brief Erases all undo data for this level
     */
    void clearUndoData( void );

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
    void addListener( LevelListener* listener );

    /*!
     * @brief Unregisters a level listener
     * @param listener A pointer to an object inheriting from LevelListener
     * @return Returns true if the listener was unregistered successfully,
     * false if otherwise
     */
    void removeListener( LevelListener* listener );

    /*!
     * @brief Overload assignment operator
     * Allows copying between level objects
     */
    Level& operator=( const Level& other );

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
    void movePlayer( char direction, bool updateUndoData = true );

    /*!
     * @brief Dispatches the set tile event
     * This occurs whenever a tile is changed
     */
    void dispatchSetTile( const std::size_t& x, const std::size_t& y, const char& tile );

    /*!
     * @brief Dispatches the move tile event
     * This occurs whenever a tile moves from an old position to a new
     * position
     */
    void dispatchMoveTile( const std::size_t& oldX, const std::size_t& oldY, const std::size_t& newX, const std::size_t& newY );

    std::string                         m_LevelName;
    std::map<std::string, std::string>  m_MetaData;
    std::vector<std::string>            m_HeaderData;
    std::vector<std::string>            m_Notes;

    TileField                           m_LevelArray;
    TileField                           m_InitialLevelArray;

    std::vector<char>                   m_UndoData;

    std::vector<LevelListener*>         m_LevelListeners;

    std::size_t                         m_PlayerX;
    std::size_t                         m_PlayerY;
    std::size_t                         m_UndoDataPos;

    bool                                m_IsLevelValid;
};

} // namespace Chocobun

#endif // __CHOCOBUN_CORE_LEVEL_HPP__
