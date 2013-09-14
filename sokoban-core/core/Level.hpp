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

private:

    std::vector< std::vector<char> > m_LevelArray;
    std::map<std::string, std::string> m_MetaData;
    std::vector<char> m_UndoData;

};

} // namespace Sokoban

#endif // __SOKOBAN_CORE_LEVEL_HPP__
