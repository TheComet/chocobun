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
// App
// --------------------------------------------------------------

#ifndef __APP_HPP__
#define __APP_HPP__

// --------------------------------------------------------------
// include files

#include <iostream>
#include <vector>
#include <ChocobunInterface.hpp>

// --------------------------------------------------------------
// forward declarations

namespace Chocobun {
    class Collection;
}

/*!
 * @brief The application object
 */
class App :
    public Chocobun::LevelListener
{
public:

    /*!
     * @brief Constructor
     */
    App( void );

    /*!
     * @brief Destructor
     */
    ~App( void );

    /*!
     * @brief Launches the application
     *
     * @note Will throw std::exception if anything fails
     */
    void go( void );

private:

    /*!
     * @brief Splits the input command into a list of arguments and options
     *
     * @param input The input string to split
     * @param argList The output argument list to write the arguments to
     * @param optionList The output option list to write the option parameters to
     * @return If the input string was invalid, false is returned, otherwise true is returned
     */
    bool splitCommand( const std::string& in, std::vector<std::string>& argList, std::vector<std::string>& optionList );

    /*!
     * @brief Displays help text for a specific command
     */
    bool displayHelp( const std::string& cmd );

    void onSetTile( const std::size_t& x, const std::size_t& y, const char& tile );

    Chocobun::Collection* m_Collection;
    std::string m_FileFormat;
};

#endif // __APP_HPP__
