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
// Array2D.hpp
// --------------------------------------------------------------

// --------------------------------------------------------------
// include files

#include <iostream>
#include <vector>

namespace Chocobun {

/*!
 * @brief Wraps a dynamic 2-dimensional array with std::vector< std::vector<T> > at its core
 */
template <class T>
class Array2D
{
public:

    /*!
     * @brief Default constructor
     */
    Array2D( void );

    /*!
     * @brief Constructor setting the default content of the array
     * see @a setDefaultContent for more information
     * @param content The content to use
     */
    Array2D( const T& content );

    /*!
     * @brief Copy Constructor
     * @param cp The other 2D array to copy
     */
    Array2D( const Array2D& that );

    /*!
     * @brief Copy Constructor with setting the default content of the array
     */
    Array2D( const Array2D& that, const T& content );

    /*!
     * @brief Default destructor
     */
    ~Array2D( void );

    /*!
     * @brief Sets the default initial content of the array
     * Sets what content should be inserted into the array
     * when first allocated or cleared.
     * @param content The content to use
     */
    void setDefaultContent( const T& content );

    /*!
     * @brief Retrieves the default content of the array
     */
    const T& getDefaultContent( void ) const;

    /*!
     * @brief Resizes the Array2D to the specified dimensions
     * @param x The new x-size
     * @param y The new y-size
     */
    void resize( const std::size_t& x, const std::size_t& y );

    /*!
     * @brief Gets the size of the array in the x dimension
     * @return std::size_t of the array's x dimension
     */
    const std::size_t& sizeX( void ) const;

    /*!
     * @brief Gets the size of the array in the y dimension
     * @return std::size_t of the array's y dimension
     */
    const std::size_t& sizeY( void ) const;

    /*!
     * @brief Gets a character from the array at the specified coordinates
     * Enables the use of reading from the Array2D with boundary checking
     * @exception Throws a Chocobun::Exception if the coordinates are
     * out of bounds
     * @return The data stored at the specified coordinates
     */
    const T& at( const std::size_t& x, const std::size_t& y ) const;

    /*!
     * @brief Gets a character from the array at the specified coordinates
     * Enables the use of writing to the array with boundary checking
     * @exception Throws a Chocobun::Exception if the coordinates are
     * out of bounds
     * @return The data stored at the specified coordinates
     */
    T& at( const std::size_t& x, const std::size_t& y );

    /*!
     * @brief Overload assignment operator
     */
    Array2D<T>& operator=( const Array2D<T>& that );

    /*!
     * @brief Subscript operator overload
     * Enables the use of writing to the Array2D using [][]
     */
    std::vector<T>& operator[]( const std::size_t& index );

    /*!
     * @brief Subscript operator overload
     * Enables the use of reading from the Array2D using [][]
     */
    const std::vector<T>& operator[]( const std::size_t& index ) const;

private:

    T                               m_DefaultContent;
    std::size_t                     m_SizeX;
    std::size_t                     m_SizeY;
    std::vector< std::vector<T> >   m_Array; // NOTE: outer vector: x-dimension, inner vector: y-dimension
};

} // namespace Chocobun
