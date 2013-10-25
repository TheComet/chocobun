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
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with Chocobun. If not, see <http://www.gnu.org/licenses/>.
*/

// --------------------------------------------------------------
// TileManipulator.hpp
// --------------------------------------------------------------

// --------------------------------------------------------------
// include files

#include <vector>

namespace Chocobun {

// --------------------------------------------------------------
// forward declarations

template <class COORD>
class TileManipulator
{
public:

    /*!
     * @brief Listener interface class for tile manipulation notifications
     */
    class Listener
    {
    protected:

        void onMoveTile( const COORD& oldPos, const COORD& newPos );
        void onSetTile( const COORD& pos, const char& tile );
    };

    /*!
     * @brief Default constructor
     */
    TileManipulator( void );

    /*!
     * @brief Default destructor
     */
    virtual ~TileManipulator( void );

    /*!
     * @brief Moves a tile from one position to another
     */
    void moveTile( const COORD& oldPos, const COORD& newPos ) const;

    /*!
     * @brief Changes the tile from one type to another
     */
    void setTile( const COORD& pos, const char& tile ) const;

    /*!
     * @brief Add a listener to be informed about tile manipulations
     */
    void addListener( const Listener* listener );

    /*!
     * @brief Remove a registered listener
     */
    void removeListener( const Listener* listener);

protected:

    /*!
     * @brief Abstract method for moving a tile from one position to another
     * If the method is not implemented by its derived class, the listeners
     * will not be informed about any tile moves, even if @a moveTile is
     * called. In order to enable listener notifications, the derived class
     * must return **true**. Returning **false** will disable notifications
     * for tile moves.
     * @param oldPos The coordinates of the tile to move
     * @param newPos The destination coordinates of the selected tile
     * @return True to notify listeners, false to not notify listeners
     */
    virtual bool _moveTile( const COORD& oldPos, const COORD& newPos );

    /*!
     * @brief Abstract method for changing a tile from one type to another
     * If the method is not implemented by its derived class, the listeners
     * will not be informed about any tile changes, even if @a setTile is
     * called. In order to enable listener notifications, the derived class
     * must return **true**. Returning **false** will disable notifications
     * for tile changes.
     * @param pos The coordinates of the tile to set
     * @param tile The type of tile to change it to
     * @return True to notify listeners, false to not notify listeners
     */
    virtual bool _setTile( const COORD& pos, const char& tile );

private:

    /*!
     * @brief Dispatches a tile move event to all registered listeners
     */
    void dispatchMoveTile( const COORD& oldPos, const COORD& newPos ) const;

    /*!
     * @brief Dispatches a tile set event to all registered listeners
     */
    void dispatchSetTile( const COORD& pos, const char& tile ) const;

    std::vector<Listener*> m_Listeners;

};

} // namespace Chocobun
