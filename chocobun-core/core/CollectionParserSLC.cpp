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
// CollectionParserSLC.cpp
// --------------------------------------------------------------

// TODO Make sure to call this->convertTilesToConvetional( tileString ) on
// tiles before adding them to the level. More details in issue #7
// (the method above is a base class of CollectionParserSLC)

// --------------------------------------------------------------
// include files

#include <core/Collection.hpp>
#include <core/CollectionParserSLC.hpp>
#include <core/Level.hpp>
#include <core/Exception.hpp>

#include <fstream>
#include <sstream>
#include <algorithm>  // std::find

#include <rapidxml-1.13/rapidxml.hpp>
#include <rapidxml-1.13/rapidxml_print.hpp>

namespace Chocobun {

const int CollectionParserSLC::NUM_META_TAG_NAMES = 4;
const char* CollectionParserSLC::META_TAG_NAMES[] = {"Title", "Description", "Email", "Url"};
const char* CollectionParserSLC::EXPECTED_TAG_NAMES[] = {"SokobanLevels", "Title", "LevelCollection"};

// --------------------------------------------------------------
CollectionParserSLC::CollectionParserSLC( void )
{
}

// --------------------------------------------------------------
CollectionParserSLC::~CollectionParserSLC( void )
{
}

// --------------------------------------------------------------
void CollectionParserSLC::_parse( std::ifstream& file, Collection& collection )
{
    rapidxml::xml_document<> doc;

    // Read file into vector<char>
    std::vector<char> buffer( ( std::istreambuf_iterator<char>( file ) ), std::istreambuf_iterator<char>( ) );
    buffer.push_back( '\0' );

    try
    {
        // parse the darn thing with rapidxml
        doc.parse<0>( &buffer[0] );
    }
    catch( rapidxml::parse_error& e )
    {
        throw Exception( std::string("Error during xml parsing: ") + e.what() );
    }

    rapidxml::xml_node<>* rootNode = getFirstNode( &doc, "SokobanLevels" );

    // read all the meta tags into the metaTagValues array
    std::string metaTagValues [NUM_META_TAG_NAMES];
    for( int i = 0; i < NUM_META_TAG_NAMES; ++i )
    {
        rapidxml::xml_node<>* metaTag = getFirstNode( rootNode, META_TAG_NAMES[i] );
        if (metaTag != 0) // if there actually is such a meta tag
        {
            metaTagValues[i] = metaTag->value();
        }
    }

    rapidxml::xml_node<>* levelCollectionNode = getFirstNode(rootNode, "LevelCollection");

    std::string levelCollectionCopyright = getFirstAttribute(levelCollectionNode, "Copyright");

    for( rapidxml::xml_node<>* levelNode = levelCollectionNode->first_node("Level"); levelNode; levelNode = levelNode->next_sibling() )
    {
        std::string levelName = getFirstAttribute(levelNode, "Id");

        Level* lvl; // = listener->_constructNewLevel();

        lvl->addMetaData("Author", levelCollectionCopyright);

        // set the meta tags from the collection tag for the level
        for( int i = 0; i < NUM_META_TAG_NAMES; ++i )
        {
            lvl->addMetaData(META_TAG_NAMES[i], metaTagValues[i]);
        }

        //listener->_generateLevelName( levelName );
        lvl->setLevelName( levelName );

        int y = 0;

        for( rapidxml::xml_node<>* levelLineNode = levelNode->first_node("L"); levelLineNode; levelLineNode = levelLineNode->next_sibling() )
        {
            lvl->insertTileLine(y++, levelLineNode->value());
        }
    }

    //TODO return metaTagValues[0];
}

// --------------------------------------------------------------
void CollectionParserSLC::_save( std::ofstream& file, const Collection& collection )
{
    rapidxml::xml_document<> doc;
    rapidxml::xml_node<>* declaration = doc.allocate_node( rapidxml::node_declaration );
    declaration->append_attribute( doc.allocate_attribute( "version", "1.0" ) );
    declaration->append_attribute( doc.allocate_attribute( "encoding", "UTF-8" ) );
    doc.append_node( declaration );

    rapidxml::xml_node<>* root = doc.allocate_node( rapidxml::node_element, "SokobanLevels" );
    root->append_attribute( doc.allocate_attribute( "xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance" ) );
    root->append_attribute( doc.allocate_attribute( "xsi:schemaLocation", "SokobanLev.xsd" ) );
    doc.append_node( root );

    Level* lvl; // = levels[0];
    for( int i = 0; i < NUM_META_TAG_NAMES; ++i )
    {
        std::string tagName = META_TAG_NAMES[i];

        rapidxml::xml_node<>* metaDataNode = doc.allocate_node( rapidxml::node_element, doc.allocate_string(tagName.c_str()) );
        metaDataNode->value( doc.allocate_string( lvl->getMetaData(tagName).c_str() ) );
        root->append_node( metaDataNode );
    }

    rapidxml::xml_node<>* levelCollectionNode = doc.allocate_node( rapidxml::node_element, doc.allocate_string("LevelCollection") );

    // TODO issue #11 -Level::getMetaData() will throw an unhandled exception if the requested meta data doesn't exist
    levelCollectionNode->append_attribute( doc.allocate_attribute( "Copyright", lvl->getMetaData("Author").c_str() ) );

    std::stringstream ss1;
    ss1 <<  this->getMaxLevelWidth();
    std::string ss1s = ss1.str();
    levelCollectionNode->append_attribute( doc.allocate_attribute( "MaxWidth", ss1s.c_str() ) );

    std::stringstream ss2;
    ss2 <<  this->getMaxLevelHeight();
    std::string ss2s = ss2.str();
    levelCollectionNode->append_attribute( doc.allocate_attribute( "MaxHeight", ss2s.c_str() ) );

    const char* attributeValue;

    std::stringstream ss3;
    std::stringstream ss4;

    /*for ( std::vector<Level*>::iterator it = levels.begin(); it != levels.end(); ++it )
    {
        rapidxml::xml_node<>* levelNode = doc.allocate_node( rapidxml::node_element, doc.allocate_string("Level") );

        levelNode->append_attribute( doc.allocate_attribute( "Id", (*it)->getLevelName().c_str() ) );

        ss3.str("");
        ss3 <<  (*it)->getSizeX();

        attributeValue = doc.allocate_string( ss3.str().c_str() );
        levelNode->append_attribute( doc.allocate_attribute( "Width", attributeValue ) );

        ss4.str("");
        ss4 <<  (*it)->getSizeY();

        attributeValue = doc.allocate_string( ss4.str().c_str() );
        levelNode->append_attribute( doc.allocate_attribute( "Height", attributeValue ) );

        std::stringstream ss;
        (*it)->streamInitialTileData( ss );
        std::istringstream levelData( ss.str() );
        std::string line;

        while( std::getline( levelData, line ) ) {
            rapidxml::xml_node<>* lineNode = doc.allocate_node( rapidxml::node_element, doc.allocate_string("L") );
            lineNode->value( doc.allocate_string( line.c_str() ) );
            levelNode->append_node( lineNode );
        }

        levelCollectionNode->append_node(levelNode);

        // TODO issue #12 - Implement the methods Level::exportUndoData() and Level::importUndoData()

    }*/

    root->append_node( levelCollectionNode );

    file << doc;
}

// --------------------------------------------------------------
rapidxml::xml_node<>* CollectionParserSLC::getFirstNode( rapidxml::xml_node<> * superNode, const char * name)
{
    rapidxml::xml_node<>* node = superNode->first_node(name);

    if (node == 0)
    {
        const char ** p = std::find( EXPECTED_TAG_NAMES, EXPECTED_TAG_NAMES+3, name );
        if( p != EXPECTED_TAG_NAMES+3 ) // name is in the EXCPECTED_TAG_NAMES
        {
            throw Exception( std::string("[CollectionParserSLC::parse] Expected node with name ") + name + " was not found" );
        }
    }

    return node;
}

// --------------------------------------------------------------
const char * CollectionParserSLC::getFirstAttribute( rapidxml::xml_node<> * node, const char * name)
{
    rapidxml::xml_attribute<char> * attribute = node->first_attribute(name);

    if (attribute == 0) throw Exception( std::string("[CollectionParserSLC::parse] Expected attribute with name ") + name + " was not found" );

    return attribute->value();
}

} // namespace Chocobun
