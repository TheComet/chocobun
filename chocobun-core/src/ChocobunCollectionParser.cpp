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

#include <ChocobunCollection.hpp>
#include <ChocobunCollectionParser.hpp>
#include <ChocobunCollectionParserSOK.hpp>
#include <ChocobunCollectionParserSLC.hpp>
#include <ChocobunRLE.hpp>
#include <ChocobunLevel.hpp>
#include <ChocobunException.hpp>
#include <ChocobunConfig.hpp>
#include <fstream>
#include <sstream>
#include <memory>

namespace Chocobun {

// --------------------------------------------------------------
CollectionParser::CollectionParser( void ) :
	m_FileFormat( "SOK" )
{
}

// --------------------------------------------------------------
CollectionParser::~CollectionParser( void )
{
}

// --------------------------------------------------------------
void CollectionParser::parse( const std::string& fileName, Collection& collection )
{

    // open the file
    std::ifstream file( fileName.c_str() );
    if( !file.is_open() )
        throw Exception( "[CollectionParser::parse] Error: attempt to open collection file failed" );

    std::string inBuf("");
    std::getline( file, inBuf );
    file.seekg( 0 ); // reset file pointer

    // wrap pointer into smart pointer so exceptions can be thrown
    // without memory leaks
    std::auto_ptr<CollectionParserBase> parser;

    if( "<?xml" == inBuf.substr(0,5) ) // if the file starts with the xml magic bytes, we assume the format is SLC...
    {
        parser = std::auto_ptr<CollectionParserBase>( new CollectionParserSLC() );
    }
    else // ... else we assume the file format is SOK
    {
        parser = std::auto_ptr<CollectionParserBase>( new CollectionParserSOK() );
    }

    // parse
    parser->parse( file, collection );
}

// --------------------------------------------------------------
void CollectionParser::save( const std::string& fileName, const Collection& collection, bool enableCompression )
{

    std::string tempFileName = fileName; tempFileName.append( "~" );
    std::ofstream file( tempFileName.c_str(), std::ofstream::out );
    if( !file.is_open() )
        throw Exception( "[CollectionParser::save] unable to open file for saving" );

    // wrap pointer into smart pointer so exceptions can be thrown
    // without memory leaks
    std::auto_ptr<CollectionParserBase> parser;

    for(;;)
    {
        if( this->getFileFormat().compare("SLC") == 0 )
        {
            parser = std::auto_ptr<CollectionParserBase>( new CollectionParserSLC() );
            break;
        }

        if( this->getFileFormat().compare("SOK") == 0 )
        {
            parser = std::auto_ptr<CollectionParserBase>( new CollectionParserSOK() );
            break;
        }
        throw Exception( "[CollectionParser::save] Error: unknown file format \"" + this->getFileFormat() + "\"");
    }

    if( enableCompression ) parser->enableCompression();
    parser->save( file, collection );

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

// --------------------------------------------------------------
void CollectionParser::setFileFormat( const std::string& fileFormat )
{
    this->m_FileFormat = fileFormat;
}

// --------------------------------------------------------------
const std::string& CollectionParser::getFileFormat() const
{
    return this->m_FileFormat;
}
} // namespace Chocobun
