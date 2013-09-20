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
// SLC parser
// --------------------------------------------------------------

#ifndef __CHOCOBUN_CORE_COLLECTION_PARSER_SLC_HPP__
#define __CHOCOBUN_CORE_COLLECTION_PARSER_SLC_HPP__

// --------------------------------------------------------------
// include files

#include <core/CollectionParserBase.hpp>

class CollectionParserSLC : public CollectionParserBase
{
public:
   CollectionParserSLC(){}
};

// namespace Chocobun {

// /*!
//  * @brief Universal .SLC format parser
//  *
//  * See http://sokobano.de/wiki/index.php?title=Sok_format for more information
//  */
// class CollectionParserSLC :
//     public CollectionParserBase
// {
// public:

//     /*!
//      * @brief Constructor
//      */
//     CollectionParserSLC( void );

//     /*!
//      * @brief Destructor
//      */
//     ~CollectionParserSLC( void );

//     /*!
//      * @brief Parses a .SLC file
//      *
//      * See http://sokobano.de/wiki/index.php?title=Sok_format for more information
//      *
//      * @param file An open file object to read from
//      * @param levelMap An std::vector of levels to write to
//      * @return Returns the name of the collection (if any), otherwise the string
//      * is empty
//      */
//     std::string parse( std::ifstream& file, std::vector<Level*>& levelMap );

//     !
//      * @brief Universal .SLC format exporter
//      *
//      * See http://sokobano.de/wiki/index.php?title=Sok_format for more information
//      *
//      * @param file An open file object to write data to
//      * @param levelMap An std::vector of levels to read from
     
//     void save( const std::string& collectionName, std::ofstream& file, std::vector<Level*>& levels );

//     /*!
//      * @brief Enables RLE compression for tile data when exporting
//      * @note Default is <b>disabled</b>
//      */
//     void enableCompression( void );

//     /*!
//      * @brief Disables RLE compression for tile data when exporting
//      * @note Default is <b>disabled</b>
//      */
//     void disableCompression( void );

// private:

//     /*!
//      * @brief Returns true if the string is level data
//      */
//     bool isLevelData( const std::string& str );

//     /*!
//      * @brief Extracts key value pairs and returns true or false if successful
//      *
//      * @param str The string to search for key-value pairs
//      * @param key Output string where the key is written to
//      * @param value Output string where the value is written to
//      * @return True if a key-value pair was found, false if otherwise
//      */
//     bool getKeyValuePair( const std::string& str, std::string& key, std::string& value );

//     bool m_EnableRLE;

// };

// } // namespace Chocobun

#endif // __CHOCOBUN_CORE_COLLECTION_PARSER_SLC_HPP__
