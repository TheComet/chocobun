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
     * @brief Expose level iterators
     */
    typedef std::vector<Level*>::iterator       level_iterator;
    typedef std::vector<Level*>::const_iterator const_level_iterator;

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
     * Unloads everything (this calls @a unload)
     */
    ~Collection( void );

/*
    void load( const std::string& fileName );

    void save( const std::string& fileFormat );

    void unload( void );

    void setName( const std::string& name );

    const std::string& getName( void ) const;

    void enableCompression( void );

    void disableCompression( void );

    bool isCompressionEnabled( void ) const;

    Level* addLevel( void );

    void removeLevel( Level* lvl );

    void removeLevel( const std::string& levelName );

    void generateLevelName( std::string& name );

    Level* getLevelPtr( const std::string& levelName );

    Level& getLevel( const std::string& levelName );

    void getLevelNames( std::vector<std::string>& vs );

    void streamLevelNames( std::ostream& stream );

    void selectFirstLevel( void );

    void selectLastLevel( void );

    bool selectNextLevel( void );

    bool selectPreviousLevel( void );

    void selectActiveLevel( const std::string& levelName );

    bool hasActiveLevel( void );

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

    Collection& operator=( const Collection& that );
*/
private:

    std::string m_FileName;
    std::string m_CollectionName;
    std::vector<Level*> m_Levels;
    std::vector<LevelListener*> m_LevelListeners;
    std::size_t m_ActiveLevel;
    bool m_EnableCompression;
    bool m_IsLoaded;
};

} // namespace Chocobun

#endif // __CHOCOBUN_CORE_COLLECTION_HPP__
