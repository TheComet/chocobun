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
// Level
// --------------------------------------------------------------

#ifndef __SOKOBAN_CORE_LEVEL_HPP__
#define __SOKOBAN_CORE_LEVEL_HPP__

// --------------------------------------------------------------
// include files

#include <core/Config.hpp>

#include <string>
#include <vector>
#include <map>

#include <iostream>

namespace Sokoban {

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
     * -Collection
     * -Author
     *
     * @note Keys are case sensitive and should be converted to lower case
     * before adding the meta data.
     *
     * @exception Sokoban::Exception If the key already exists
     *
     * @param key The key of the entry (used to get the data back later on)
     * @param value The value of the entry (can by any text string)
     */
    void addMetaData( const std::string& key, const std::string& value );

    /*!
     * @brief Retrieves meta data of the level
     *
     * @exception Sokoban::Exception if the key was not found
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
     * @brief Adds comments and other text for this level
     *
     * This is used later on when the file is saved to disk again,
     * so comments that would not normally be loaded are preserved
     *
     * @param comment Comment to add
     */
    void addCommentData( const std::string& comment );

    /*!
     * @brief Removes a comment from this level
     *
     * This is called when a level name is discovered. Because
     * there can be multiple passes of delay before a level name can
     * be confirmed, it usually occurs that it has been added as a
     * comment first. This will remove it again so it isn't exported twice.
     *
     * @param comment The comment string to remove
     */
    void removeCommentData( const std::string& comment );

    /*!
     * @brief Streams all comment data to a stream object
     *
     * This is used to save the comment data of a level
     *
     * @param stream The stream object to stream to
     */
    void streamAllCommentData( std::ostream& stream );

    /*!
     * @brief Inserts a tile into the level at the given coordinate
     *
     * Internally the map array is resized accordingly so it remains square.
     * Valid tile characters are:
     * -# Wall
     * -@ Pusher
     * -+ Pusher on goal square
     * -$ Box
     * -* Box on goal square
     * -. Goal square
     * -  Floor (space)
     * -_ Floor
     *
     * @exception Sokoban::Exception if an invalid character is passed
     *
     * @param x The X coordinate for the tile to insert
     * @param y The Y coordinate for the tile to insert
     * @param tile The type of tile
     */
    void insertTile( const Sokoban::Uint32& x, const Sokoban::Uint32& y, const char& tile );

    /*!
     * @brief Inserts a whole line instead of a single tile
     *
     * Internally the map array is resized accordingly so it remains square.
     * Valid tile characters are:
     * -# Wall
     * -@ Pusher
     * -+ Pusher on goal square
     * -$ Box
     * -* Box on goal square
     * -. Goal square
     * -  Floor (space)
     * -_ Floor
     *
     * @exception Sokoban::Exception if an invalid character is passed
     *
     * @param y The Y coordinate for the tile line to insert
     * @param tiles The line of tiles to insert
     */
    void insertTileLine( const Sokoban::Uint32& y, const std::string& tiles );

    /*!
     * \brief Streams all tile data to a stream object
     *
     * This is used to save the level data to a file
     *
     * @param stream The stream object to stream to
     */
    void streamAllTileData( std::ostream& stream );

private:

    std::vector< std::vector<char> > m_LevelArray;
    std::map<std::string, std::string> m_MetaData;
    std::vector<std::string> m_Comments;
    std::vector<char> m_UndoData;

};

} // namespace Sokoban

#endif // __SOKOBAN_CORE_LEVEL_HPP__
