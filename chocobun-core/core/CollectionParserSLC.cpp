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

// --------------------------------------------------------------
// include files

#include <core/CollectionParserSLC.hpp>
#include <core/Level.hpp>

#include <fstream>
#include <sstream>
#include <algorithm>

#include <rapidxml-1.13/rapidxml.hpp>

namespace Chocobun {

const int CollectionParserSLC::NUM_META_TAG_NAMES = 4;
const char* CollectionParserSLC::META_TAG_NAMES[] = {"Title", "Description", "Email", "Url"};

// --------------------------------------------------------------
CollectionParserSLC::CollectionParserSLC( void )
{
}

// --------------------------------------------------------------
CollectionParserSLC::~CollectionParserSLC( void )
{
}

// --------------------------------------------------------------
std::string CollectionParserSLC::_parse( std::ifstream& file, std::vector<Level*>& levels )
{
    rapidxml::xml_document<> doc;

    // Read file into vector<char>
    std::vector<char> buffer( ( std::istreambuf_iterator<char>( file ) ), std::istreambuf_iterator<char>( ) );
    buffer.push_back( '\0' );

    // parse the darn thing with rapidxml
    doc.parse<0>( &buffer[0] ); 

    rapidxml::xml_node<>* rootNode = doc.first_node("SokobanLevels");

    // read all the meta tags into the metaTagValues array
    std::string metaTagValues [NUM_META_TAG_NAMES];
    for( int i = 0; i < NUM_META_TAG_NAMES; ++i ) 
    {
        metaTagValues[i] = rootNode->first_node(META_TAG_NAMES[i])->value();
    }

    rapidxml::xml_node<>* levelCollectionNode = rootNode->first_node("LevelCollection");

    std::string levelCollectionCopyright = levelCollectionNode->first_attribute("Copyright")->value();

    for( rapidxml::xml_node<>* levelNode = levelCollectionNode->first_node("Level"); levelNode; levelNode = levelNode->next_sibling() )
    {
        std::string levelName = levelNode->first_attribute("Id")->value();

        Level* lvl = new Level();

        lvl->addMetaData("Author", levelCollectionCopyright);

        // set the meta tags from the collection tag for the level
        for( int i = 0; i < NUM_META_TAG_NAMES; ++i ) 
        {
            lvl->addMetaData(META_TAG_NAMES[i], metaTagValues[i]);
        }

        this->_registerLevel( lvl, levelName, levels );

        int y = 0;

        for( rapidxml::xml_node<>* levelLineNode = levelNode->first_node("L"); levelLineNode; levelLineNode = levelLineNode->next_sibling() )
        {
            lvl->insertTileLine(y++, levelLineNode->value());
        }
    }

    return metaTagValues[0];
}



// --------------------------------------------------------------
void CollectionParserSLC::_save( const std::string& collectionName, std::ofstream& file, std::vector<Level*>& levels )
{
}

} // namespace Chocobun
