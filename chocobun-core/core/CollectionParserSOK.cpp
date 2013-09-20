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
// Universal .SOK parser
// --------------------------------------------------------------

// --------------------------------------------------------------
// include files

#include <core/CollectionParserSOK.hpp>
#include <core/Level.hpp>
#include <core/RLE.hpp>

#include <fstream>
#include <sstream>
#include <algorithm>

namespace Chocobun {

// --------------------------------------------------------------
CollectionParserSOK::CollectionParserSOK( void ) :
    m_EnableRLE( false )
{
}

// --------------------------------------------------------------
CollectionParserSOK::~CollectionParserSOK( void )
{
}

// --------------------------------------------------------------
bool CollectionParserSOK::isLevelData( const std::string& str )
{
    std::string levelChars( Level::validTiles + "()0123456789|" ); // RLE compression contains these characters
    Int32 threshold = 0;
    for( size_t i = 0; i != str.size(); ++i )
        if( levelChars.find(str[i]) == std::string::npos )
            threshold-=2;
        else
            ++threshold;
    return (threshold>0);
}

// --------------------------------------------------------------
bool CollectionParserSOK::getKeyValuePair( const std::string& str, std::string& key, std::string& value )
{

    size_t pos = str.find( ":" ); // key-value pairs are split by a colon
    if( pos == std::string::npos )
        return false;

    if( pos < 2 ) // empty key value pairs
        return false;

    if( str.find( "::" ) != std::string::npos ) // comments are not permitted
        return false;

    // extract key and value
    key = str.substr(0, pos);
    value = str.substr(pos+1, str.size()-pos);

    // trim key and value from leading and trailing spaces
    size_t strBegin = key.find_first_not_of( " " );
    size_t strEnd = key.find_last_not_of( " " );
    key = key.substr(strBegin, strEnd-strBegin+1);
    strBegin = value.find_first_not_of( " " );
    strEnd = value.find_last_not_of( " " );
    value = value.substr(strBegin, strEnd-strBegin+1);

    return true;
}

// --------------------------------------------------------------
std::string CollectionParserSOK::_parse( std::ifstream& file, std::vector<Level*>& levels )
{

    // the first level is a requirement
    Level* lvl = new Level();
    RLE rle;

    Uint32 tileLine = 0;
    bool lastLineWasBlank = true;
    bool isLevelData = false;
    bool lastLineWasLevelData = false;
    bool levelDataReadForFirstTime = false;
    std::string inBuf("");
    std::string oldInBuf("");
    std::string levelName("");
    std::string tempLevelName("");
    std::string collectionName("");
    while( !file.eof() )
    {

        // read line from file and filter out any blank lines
        // additionally, flag if a blank line was found and save the last line
        // in an old buffer so the title of the level can be determined later on
        lastLineWasBlank = false;
        oldInBuf = inBuf;
        while(!file.eof())
        {
            std::getline( file, inBuf );
            if( inBuf.size() > 1 )
                break;
            lastLineWasBlank = true;
        }

        // remove tabs
        inBuf.erase(std::remove(inBuf.begin(), inBuf.end(), '\t'), inBuf.end());

        // so checks are only performed once
        lastLineWasLevelData = isLevelData;
        isLevelData = this->isLevelData( inBuf );

        // requirements for a level title are:
        // - the last non-blank line before a puzzle, saved game, or solution
        // - must be preceeded by a blank line
        // - must not be a comment
        // copying the last line as the level title before getting a new line
        // from the file to meet these requirements

        if( lastLineWasBlank && oldInBuf.find("::") == std::string::npos && isLevelData && !this->isLevelData( oldInBuf ) )
        {
            std::string key("");
            std::string value("");
            if( !this->getKeyValuePair(oldInBuf, key, value) )
            {
                tempLevelName = oldInBuf;
                if( levelName.size() == 0 && !levelDataReadForFirstTime )
                    levelName = tempLevelName;
            }
        }

        // create new level if beginning of new level data has been found
        // this only works if level data has been read at least once
        if( levelDataReadForFirstTime && (!lastLineWasLevelData || lastLineWasBlank) && isLevelData )
        {
            if( levelName.size() != 0 )
            {
                lvl->removeHeaderData( levelName ); // level name was added in the last pass, remove it again
                lvl->removeLevelNote( levelName );
            }
            if( tempLevelName.size() != 0 )
            {
                lvl->removeHeaderData( tempLevelName );
                lvl->removeLevelNote( tempLevelName );
            }
            this->_registerLevel( lvl, levelName, levels );
            lvl = new Level();
            if( levelName.compare( tempLevelName ) == 0 ) tempLevelName = "";
            levelName = tempLevelName;
            tileLine = 0;
        }
        if( isLevelData )
            levelDataReadForFirstTime = true;

        // process input
        for(;;){

            // determine if if is level data
            if( isLevelData )
            {
                rle.decompress( inBuf );
                lvl->insertTileLine( tileLine, inBuf );
                ++tileLine;
                break;
            }

            // determine if it is a key-value pair
            std::string key("");
            std::string value("");
            if( this->getKeyValuePair( inBuf, key, value ) )
            {

                // special case for collection name
                if( key.compare("Collection") == 0 )
                    collectionName = value;

                // add meta data to level
                else
                    lvl->addMetaData( key, value );

                break;
            }

            // add data as comment data
            if( levelDataReadForFirstTime )
                lvl->addLevelNote( inBuf );
            else
                lvl->addHeaderData( inBuf );
            break;
        }
    }

    // register still open level
    this->_registerLevel( lvl, levelName, levels );

    return collectionName;
}

// --------------------------------------------------------------
void CollectionParserSOK::enableCompression( void )
{
    m_EnableRLE = true;
}

// --------------------------------------------------------------
void CollectionParserSOK::disableCompression( void )
{
    m_EnableRLE = false;
}

// --------------------------------------------------------------
void CollectionParserSOK::_save( const std::string& collectionName, std::ofstream& file, std::vector<Level*>& levels )
{

    // write all levels to std::cout
    file << "Collection: " << collectionName << std::endl;
    RLE rle;
    for( std::vector<Level*>::iterator it = levels.begin(); it != levels.end(); ++it )
    {

        // header data contains all unformatted text read in from the file (including comments)
        (*it)->streamAllHeaderData( file );

        // place level name above tile data between two empty lines
        file << std::endl << (*it)->getLevelName() << std::endl << std::endl;

        // write tile data with optional RLE compression
        std::stringstream ss;
        (*it)->streamAllTileData( ss, !m_EnableRLE );
        std::string compressed = ss.str();
        size_t pos = 0;
        if( m_EnableRLE ) rle.multiPassCompress( compressed );
        file << compressed;

        // add meta data below tile data
        (*it)->streamAllMetaData( file );

        // add level notes below meta data
        (*it)->streamAllNotes( file );
    }

	std::cout << "Maximum dimensions: " << this->getMaxLevelWidth() << "," << this->getMaxLevelHeigth() << std::endl;
}

} // namespace Chocobun
