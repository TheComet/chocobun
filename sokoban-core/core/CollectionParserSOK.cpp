/*
 * This file is part of Sokoban.
 *
 * Sokoban is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Sokoban is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Sokoban.  If not, see <http://www.gnu.org/licenses/>.
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

namespace Sokoban {

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
    std::string levelChars( Level::validTiles + "()0123456789" );
    Int32 threshold = 0;
    for( size_t i = 0; i != str.size(); ++i )
        if( levelChars.find_first_of(str[i]) == std::string::npos )
            threshold-=2;
        else
            ++threshold;
    return (threshold>0);
}

// --------------------------------------------------------------
bool CollectionParserSOK::getKeyValuePair( const std::string& str, std::string& key, std::string& value )
{

    size_t pos = str.find_first_of( ":" ); // key-value pairs are split by a colon
    if( pos == std::string::npos )
        return false;

    size_t pos2 = pos; // scan back until a space or tab is found
    while( str[pos2] != 32 && str[pos2] != 9 && pos2 != 0 ) --pos2;

    size_t pos3 = pos+1; // scan forward until comment starts, or end of line is found
    while( pos3 != str.size() && str[pos3] != ':' ) ++pos3;

    if( pos2 != pos && pos3 != pos+1 )
    {
        key = str.substr(pos2, pos-pos2);
        while( str[pos+1] == ' ' ) ++pos; // cut spaces preceeding value
        value = str.substr(pos+1, pos3-pos);
        return true;
    }

    return false;
}

// --------------------------------------------------------------
std::string CollectionParserSOK::parse( std::ifstream& file, std::map<std::string, Level*>& levelMap )
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
        // in an old buffer so the title of the level can be determined
        lastLineWasBlank = false;
        oldInBuf = inBuf;
        while(!file.eof())
        {
            std::getline( file, inBuf );
            if( inBuf.size() > 1 )
                break;
            lastLineWasBlank = true;
        }

        // requirements for a level title are:
        // - the last non-blank line before a puzzle, saved game, or solution
        // - must be preceeded by a blank line
        // - must not be a comment
        // copying the last line as the level title before getting a new line
        // from the file to meet these requirements

        lastLineWasLevelData = isLevelData; // so checks are only performed once
        isLevelData = this->isLevelData( inBuf );
        std::cout << inBuf << std::endl;

        if( lastLineWasBlank && oldInBuf.find("::") == std::string::npos && isLevelData )
        {
            tempLevelName = oldInBuf;
            if( levelName.size() == 0 )
                levelName = tempLevelName;
        }

        // create new level if beginning of new level data has been found
        // this only works if level data has been read at least once
        if( levelDataReadForFirstTime && (!lastLineWasLevelData || lastLineWasBlank) && isLevelData )
        {
            if( levelName.size() != 0 )
            {
                lvl->removeHeaderData( levelName ); // level name was added in the last pass, remove it again
                lvl->removeLevelNote( levelName );
                lvl->removeHeaderData( tempLevelName );
                lvl->removeLevelNote( tempLevelName );
            }
            this->registerLevel( lvl, levelName, levelMap );
            lvl = new Level();
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
            std::string key, value;
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
    this->registerLevel( lvl, levelName, levelMap );

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
void CollectionParserSOK::save( const std::string& collectionName, std::ofstream& file, std::map<std::string, Level*>& levelMap )
{

    // write all levels to std::cout
    // levels need to be written in reverse order
    file << "Collection: " << collectionName << std::endl;
    RLE rle;
    for( std::map<std::string, Level*>::iterator it = levelMap.begin(); it != levelMap.end(); ++it )
    {

        // header data contains all unformatted text read in from the file (including comments)
        it->second->streamAllHeaderData( file );

        // place level name above tile data between two empty lines
        file << std::endl << it->first << std::endl << std::endl;

        // write tile data with optional RLE compression
        it->second->streamAllTileData( file );
        /*std::stringstream ss;
        it->second->streamAllTileData( ss );
        std::string compressed = ss.str();
        if( m_EnableRLE ) rle.multiPassCompress( compressed );
        file << compressed;*/

        // add meta data below tile data
        it->second->streamAllMetaData( file );

        // add level notes below meta data
        it->second->streamAllNotes( file );
    }
}

} // namespace Sokoban
