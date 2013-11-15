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
// ChocobunTileMap.hpp
// --------------------------------------------------------------

// --------------------------------------------------------------
// include files

#include <ChocobunGraph.hxx>
#include <string>

namespace Chocobun {

// --------------------------------------------------------------
// forward declarations

template <class COORD>
class TileMap
{
public:

    struct NodeData
    {
        NodeData( char data, COORD coordinate ) : data(data), coordinate(coordinate) {}
        char data;
        COORD coordinate;
    };

    typedef Graph<COORD, std::size_t, NodeData> Graph_t;

    /*!
     * @brief Default constructor
     */
    TileMap( void );

    /*!
     * @brief Default destructor
     */
    ~TileMap( void );

    /*!
     * @brief Inserts a tile into the tile map
     * In the case of the coordinates being out of bounds, the graph is
     * resized to fit to the specified coordinates, rather than throwing
     * an error.
     * @param pos The position of the tile to insert into the graph
     * @param tile The tile to insert
     */
    void insertTile( const COORD& pos, const char& tile );

    /*!
     * @brief Inserts a line of tiles into the map
     * In the case of the coordinates being out of bounds, the graph is
     * resized to fit to the specified coordinates, rather than throwing
     * an error.
     * @note If the tile line specified by **y** already exists, it will be
     * replaced by the data passed to the function, rather than "pushed out of
     * the way" as one might have expected.
     * @param y The line to insert it into
     * @param tiles A string of tiles to insert
     */
    void insertTileLine( const std::size_t& y, const std::string& tiles );

    /*!
     * @brief Changes the type of an existing tile in the graph
     * @exception In the case of the coordinates being out of bounds, a
     * Chocobun::Exception will be thrown
     * @param pos The position of the tile to set
     * @param tile The tile to set
     */
    void setTile( const COORD& pos, const char& tile );

    /*!
     * @brief Returns the tile at the specified coordinates
     * @exception In the case of the coordinates being out of bounds, a
     * Chocobun::Exception will be thrown
     * @param pos The coordinates of the tile to retrieve
     * @return The tile
     */
    const char& getTile( const COORD& pos ) const;

    /*!
     * @brief Streams the entire content of the graph to an output stream
     * The structure of how the data is represented is entirely up to the
     * way this method is implemented.
     *
     * If the **newline** parameter is set to **false**, all new lines
     * need to be replaced with a '|' character. This is for RLE compression.
     * @param stream The output stream to stream to
     * @param newLine If set to false, insert '|' instead of new line
     */
    void streamTileMap( std::ostream& stream, bool newLine = true );

    /*!
     * @brief Returns the dimensions of the map
     * @return The dimensions
     */
    const COORD& getDimensions( void ) const;

    /*!
     * @brief Returns a reference to the underlying graph object
     */
    Graph_t& getGraph( void );

    /*!
     * @brief Returns a const reference to the underlying graph object
     */
    const Graph_t& getGraph( void ) const;

private:

    Graph_t         m_Graph;
    COORD           m_MapDimensions;
};

} // namespace Chocobun
