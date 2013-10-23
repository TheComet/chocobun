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
// TileField.hpp
// --------------------------------------------------------------

// --------------------------------------------------------------
// forward declarations

// --------------------------------------------------------------
// include files

#include <string>
#include <core/Array2D.hpp>

namespace Chocobun {

class TileField
{
public:

    /*!
     * @brief Implementation to use for the tile array
     */
    typedef Array2D<char> TileArray_t;

    /*!
     * @brief Default constructor
     */
    TileField( void );

    /*!
     * @brief Default destructor
     */
    ~TileField( void );

    void insertTile( const std::size_t& x, const std::size_t& y, const char& tile );
    void insertTileLine( const std::size_t& y, const std::string& tiles );

    void setTile( const std::size_t& x, const std::size_t& y, const char& tile );
    const char& getTile( const std::size_t& x, const std::size_t& y ) const;
    const TileArray_t& getTileArray( void ) const;
    void streamTileArray( std::ostream& stream, bool newLine = true );

    const std::size_t& getSizeX( void ) const;
    const std::size_t& getSizeY( void ) const;

private:

    Array2D<char> m_TileArray;
};

} // namespace Chocobun
