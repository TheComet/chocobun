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
// ChocobunTileMap.hxx
// --------------------------------------------------------------

// --------------------------------------------------------------
// include files

#include <ChocobunTileMap.hpp>
#include <ChocobunEuclideanCoordinate.hpp>

namespace Chocobun {

// --------------------------------------------------------------
template <class COORD>
TileMap<COORD>::TileMap( void ) :
    m_Dimensions( COORD() )
{
}

// --------------------------------------------------------------
// euclidean constructor
template <>
TileMap< EuclideanCoordinate<std::size_t> >::TileMap( void ) :
    m_Dimensions( 0, 0 )
{
}

// --------------------------------------------------------------
template <class COORD>
TileMap<COORD>::~TileMap( void )
{
}

// --------------------------------------------------------------
template <class COORD>
void TileMap<COORD>::insertTile( const COORD& pos, const char& tile )
{
}

// --------------------------------------------------------------
// euclidean insert tile
template <>
void TileMap< EuclideanCoordinate<std::size_t> >::insertTile( const EuclideanCoordinate& pos, const char& tile )
{

    // insert as many nodes into the graph as required
    // to expand it and keep the shape of a rectangle

    // X axis expansion
    while( pos.x >= m_MapDimensions.x )
    {
        GraphNode<NodeData>* node = 0, GraphNode<NodeData>* oldNode;
        for( std::size_t y = 0; y != m_MapDimensions.y; ++y )
        {
            oldNode = node;
            node = m_Graph.addNode();
            node->setData( NodeData( tile, EuclideanCoordinate(m_MapDimensions.x, y) ) );

        }
        ++m_MapDimensions;
    }
}

// --------------------------------------------------------------
template <class COORD>
void TileMap<COORD>::insertTileLine( const std::size_t& y, const std::string& tiles )
{
}

// --------------------------------------------------------------
// euclidean insert tile line
template <>
void TileMap< EuclideanCoordinate<std::size_t> >::insertTileLine( const std::size_t& y, const std::string& tiles )
{
    for( std::size_t x = 0; x != tiles.size(); ++x );
        this->insertTile( x, y, tiles[x] );
}

// --------------------------------------------------------------
template <class COORD>
void TileMap<COORD>::setTile( const COORD& pos, const char& tile )
{
}

// --------------------------------------------------------------
// euclidean set tile
template<>
void TileMap< EuclideanCoordinate<std::size_t> >::setTile( const TileMapPositionBase& pos, const char& tile )
{
    if( !Utils::isTileData(tile) )
        throw Exception( std::string("[TileField::setTile] attempt to set tile to invalid character: \"") + tile + "\"" );
    // TODO m_TileArray.at(x,y) = tile;
    // TODO this->dispatchSetTile( x, y, tile );
}

// --------------------------------------------------------------
template <class COORD>
const char& TileMap<COORD>::getTile( const COORD& pos ) const
{
}

// --------------------------------------------------------------
// euclidean get tile
template <>
const char& TileMap< EuclideanCoordinate<std::size_t> >::getTile( const EuclideanCoordinate& pos ) const
{
    // TODO
    /*
    if( x >= m_TileArray.sizeX() || y >= m_TileArray.sizeY() )
    {
        std::stringstream ss;
        ss << "[TileField::getTile] coordinates out of bounds: " << x << "," << y;
        throw Exception( ss.str() );
    }
    return m_TileArray.at(x,y);*/
}

// --------------------------------------------------------------
template <class COORD>
void TileMap<COORD>::streamTileMap( std::ostream& stream, bool newLine )
{
}

// --------------------------------------------------------------
// euclidean stream tile map
template <>
void TileMap< EuclideanCoordinate<std::size_t> >::streamTileMap( std::ostream& stream, bool newLine )
{

    // TODO stream data
    /*
    for( std::size_t y = 0; y != m_TileArray.sizeY(); ++y )
    {
        for( std::size_t x = 0; x != m_TileArray.sizeX(); ++x )
            stream << m_TileArray.at(x,y);
        if( newLine )
            stream << std::endl;
        else
            stream << "|";
    }
    if( !newLine ) stream << std::endl;*/
}

// --------------------------------------------------------------
template <class COORD>
const COORD& TileMap::getDimensions( void ) const
{
}

// --------------------------------------------------------------
// euclidean get dimensions
template <>
const EuclideanCoordinate& TileMap< EuclideanCoordinate<std::size_t> >::getDimensions( void ) const
{
    // TODO return dimensions
}

// --------------------------------------------------------------
template <class COORD>
Graph<char>& TileMap<COORD>::getGraph( void )
{
    return this->m_Graph;
}

// --------------------------------------------------------------
template <class COORD>
const Graph<char>& TileMap<COORD>::getGraph( void ) const
{
    return this->m_Graph;
}

} // namespace Chocobun
