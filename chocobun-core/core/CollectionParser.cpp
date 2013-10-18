/*
 * This file is part of Chocobun.
 *
 * Chocobun is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 
 * Chocobun is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Chocobun.  If not, see <http://www.gnu.org/licenses/>.
 */

// --------------------------------------------------------------
// CollectionParser.cpp
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
CollectionParser::CollectionParser( void ) :
	m_fileFormat( FORMAT_SOK )
{
}

// --------------------------------------------------------------
CollectionParser::~CollectionParser( void )
{
}

// --------------------------------------------------------------
// TODO Raw pointers not exception safe
std::string CollectionParser::parse( const std::string& fileName, CollectionParserListener* listener )
{

    // open the file
    std::ifstream file( fileName.c_str() );
    if( !file.is_open() )
        throw Exception( "[CollectionParser::parse] Error: attempt to open collection file failed" );

    std::string inBuf("");
    std::getline( file, inBuf );
    file.seekg( 0 ); // reset file pointer

    CollectionParserBase* parser;

    if( "<?xml" == inBuf.substr(0,5) ) // if the file starts with the xml magic bytes, we assume the format is SLC...
    {   
        parser = new CollectionParserSLC();
    }
    else // ... else we assume the file format is SOK
    {
        parser = new CollectionParserSOK();
    }

    // parse
    std::string result = parser->parse( file, listener );
    delete parser;
    return result;
}

// --------------------------------------------------------------
// TODO raw pointers not exceptoin safe
void CollectionParser::save( const std::string& collectionName, const std::string& fileName, std::vector<Level*>& levels, bool enableCompression )
{

    std::string tempFileName = fileName; tempFileName.append( "~" );
    std::ofstream file( tempFileName.c_str(), std::ofstream::out );
    if( !file.is_open() )
        throw Exception( "[CollectionParser::save] unable to open file for saving" );

    CollectionParserBase* parser;

    switch( this->getFileFormat() ) {
        case FORMAT_SLC:
            parser = new CollectionParserSLC();
            break;

        case FORMAT_SOK:
            parser = new CollectionParserSOK();
            break;
    }

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

void CollectionParser::setFileFormat( CollectionParser::FILE_FORMAT fileFormat ) 
{
    this->m_fileFormat = fileFormat;
}

CollectionParser::FILE_FORMAT CollectionParser::getFileFormat()
{
    return this->m_fileFormat;
}
} // namespace Chocobun
