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
// CollectionParserSLC.hpp
// --------------------------------------------------------------

#ifndef __CHOCOBUN_CORE_COLLECTION_PARSER_SLC_HPP__
#define __CHOCOBUN_CORE_COLLECTION_PARSER_SLC_HPP__

// --------------------------------------------------------------
// include files

#include <core/CollectionParserBase.hpp>

#include <rapidxml-1.13/rapidxml.hpp>

namespace Chocobun {

/*!
 * @brief Universal .SLC format parser
 *
 * See http://sokobano.de/wiki/index.php?title=Sok_format for more information
 */
class CollectionParserSLC :
    public CollectionParserBase
{
public:

    static const int NUM_META_TAG_NAMES;
    static const char* META_TAG_NAMES[];
    static const char* EXPECTED_TAG_NAMES[];

    /*!
     * @brief Constructor
     */
    CollectionParserSLC( void );

    /*!
     * @brief Destructor
     */
    ~CollectionParserSLC( void );

private:

	/*!
     * @brief Parses a .SLC file
     *
     * @param file An open file object to read from
     * @param levelMap An std::vector of levels to write to
     * @return Returns the name of the collection (if any), otherwise the string
     * is empty
     */
    void _parse( std::ifstream& file, Collection& collection );

    /* !
     * @brief .SLC format exporter
     *
     * @param file An open file object to write data to
     * @param levelMap An std::vector of levels to read from
     */
    void _save( std::ofstream& file, const Collection& collection );

    /* !
     * @brief Exception checking wrapper for rapidxml::xml_node#first_node
     *
     * @param superNode the node in which you wish to find the first child node
     * @param name the name of the child node you wish to find
     * @return the node if it was found, 0 otherwise
     * @throws a Chocobun::Exception in case the node was not found and is not optional
     */
    rapidxml::xml_node<>* getFirstNode( rapidxml::xml_node<> * superNode, const char * name);

    /* !
     * @brief Exception checking wrapper for rapidxml::xml_node#first_attribute
     *
     * @param node the node in which you wish to find the first attribute
     * @param name the name of the attribute you wish to find
     * @return the value string of the attribute
     * @throws a Chocobun::Exception in case the attribute was not found
     */
    const char * getFirstAttribute( rapidxml::xml_node<> * node, const char * name);

};

} // namespace Chocobun

#endif // __CHOCOBUN_CORE_COLLECTION_PARSER_SLC_HPP__
