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
// Collection Parser
// --------------------------------------------------------------

// --------------------------------------------------------------
// include files

#include <core/CollectionParser.hpp>
#include <core/CollectionParserSOK.hpp>
#include <core/CollectionParserSLC.hpp>
#include <core/RLE.hpp>
#include <core/Level.hpp>
#include <core/Exception.hpp>
#include <core/Config.hpp>
#include <fstream>
#include <sstream>

namespace Chocobun {

// --------------------------------------------------------------
CollectionParser::CollectionParser( void )
{
}

// --------------------------------------------------------------
CollectionParser::~CollectionParser( void )
{
}

// --------------------------------------------------------------
std::string CollectionParser::parse( const std::string& fileName, std::vector<Level*>& levels )
{

    // open the file
    std::ifstream file( fileName.c_str() );
    if( !file.is_open() )
        throw Exception( "[CollectionParser::parse] attempt to open collection file failed" );

    // TODO determine file format
    CollectionParserBase* parser = new CollectionParserSOK();

    // parse
    std::string result = parser->parse( file, levels );
    delete parser;
    return result;
}

// --------------------------------------------------------------
void CollectionParser::save( const std::string& collectionName, const std::string& fileName, std::vector<Level*>& levels, bool enableCompression )
{

    std::string tempFileName = fileName; tempFileName.append( "~" );
    std::ofstream file( tempFileName.c_str(), std::ofstream::out );
    if( !file.is_open() )
        throw Exception( "[CollectionParser::save] unable to open file for saving" );

    // default export format is SOK
    CollectionParserBase* parser = new CollectionParserSOK();
    if( enableCompression ) parser->enableCompression();
    parser->save( collectionName, file, levels );
    delete parser;

    // replace original with saved file
    /*
    if( remove( fileName.c_str() ) ) throw Exception( "[CollectionParser::save] Failed to replace save file with original\
                                                    file. Your progress has been saved to a temporary file with the same\
                                                    file name as the original, but with an additional \"~\" character.\
                                                    Try manually merging them.");
    if( rename( tempFileName.c_str(), fileName.c_str() ) ) throw Exception( "[CollectionParser::save] \
                                                    Failed to replace original save file with temporary. Your progress\
                                                    has been saved to a temporary file with the same file name as the\
                                                    original, but with an additional \"~\" character. Try manually renaming it.");
*/
}

} // namespace Chocobun
