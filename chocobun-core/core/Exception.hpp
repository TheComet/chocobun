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
// Exception
// --------------------------------------------------------------

#ifndef __CHOCOBUN_CORE_EXCEPTION_HPP__
#define __CHOCOBUN_CORE_EXCEPTION_HPP__

// --------------------------------------------------------------
// include files

#include <exception>

namespace Chocobun {

/*!
 * @brief Simple exception class used throughout chocobun-core
 */
class Exception :
    public std::exception
{
public:

    /*!
     * @brief Constructor
     *
     * @param message A string for identifying the error that has occured
     */
    Exception( const char* message ) throw() : m_Message(message) {}

    /*!
     * @brief Destructor
     */
    ~Exception( void ) throw() {}

    /*!
     * @brief Gets the message of the error
     * @note Overridden from std::exception's "what()" method
     */
    const char* what( void ) const throw() { return m_Message; }

private:
    const char* m_Message;
};

} // namespace Chocobun

#endif // __CHOCOBUN_CORE_EXCEPTION_HPP__
