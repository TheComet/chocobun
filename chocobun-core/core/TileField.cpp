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
// TileField.cpp
// --------------------------------------------------------------

// --------------------------------------------------------------
// include files

#include <core/Utils.hpp>
#include <core/TileField.hpp>

#include <sstream>

namespace Chocobun {

// --------------------------------------------------------------
TileField::TileField( void )
{
}

// --------------------------------------------------------------
TileField::~TileField( void )
{
}

// --------------------------------------------------------------
void TileField::insertTile( const std::size_t& x, const std::size_t& y, const char& tile )
{

    // resize array if necessary
    if( x+1 > m_TileArray.sizeX() )
        m_TileArray.resize( x+1, m_TileArray.sizeY() );
    if( y+1 > m_TileArray.sizeY() )
        m_TileArray.resize( m_TileArray.sizeX(), y+1 );

    // write tile
    this->setTile( x, y, tile );
}

// --------------------------------------------------------------
void TileField::insertTileLine( const std::size_t& y, const std::string& tiles )
{
    for( std::size_t x = 0; x != tiles.size(); ++x )
        this->insertTile( x, y, tiles[x] );
}

// --------------------------------------------------------------
void TileField::setTile( const std::size_t& x, const std::size_t& y, const char& tile )
{
    if( !Utils::isTileData(tile) )
        throw Exception( std::string("[TileField::setTile] attempt to set tile to invalid character: \"") + tile + "\"" );
    m_TileArray.at(x,y) = tile;
    // TODO this->dispatchSetTile( x, y, tile );
}

// --------------------------------------------------------------
const char& TileField::getTile( const std::size_t& x, const std::size_t& y ) const
{
    if( x >= m_TileArray.sizeX() || y >= m_TileArray.sizeY() )
    {
        std::stringstream ss;
        ss << "[TileField::getTile] coordinates out of bounds: " << x << "," << y;
        throw Exception( ss.str() );
    }
    return m_TileArray.at(x,y);
}

// --------------------------------------------------------------
const TileField::TileArray_t& TileField::getTileArray( void ) const
{
    return m_TileArray;
}

// --------------------------------------------------------------
void TileField::streamTileArray( std::ostream& stream, bool newLine )
{

    // stream data
    for( std::size_t y = 0; y != m_TileArray.sizeY(); ++y )
    {
        for( std::size_t x = 0; x != m_TileArray.sizeX(); ++x )
            stream << m_TileArray.at(x,y);
        if( newLine )
            stream << std::endl;
        else
            stream << "|";
    }
    if( !newLine ) stream << std::endl;
}

// --------------------------------------------------------------
const std::size_t& TileField::getSizeX( void ) const
{
    return m_TileArray.sizeX();
}

// --------------------------------------------------------------
const std::size_t& TileField::getSizeY( void ) const
{
    return m_TileArray.sizeY();
}

} // namespace Chocobun
