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
// Collection Parser
// --------------------------------------------------------------

// --------------------------------------------------------------
// include files

#include <core/CollectionParser.hpp>
#include <core/RLE.hpp>
#include <core/Level.hpp>
#include <core/Exception.hpp>
#include <core/Config.hpp>
#include <fstream>
#include <iostream>
#include <sstream>

namespace Sokoban {

// --------------------------------------------------------------
CollectionParser::CollectionParser( void )
{
}

// --------------------------------------------------------------
CollectionParser::~CollectionParser( void )
{
}

// --------------------------------------------------------------
void CollectionParser::parse( const std::string& fileName, std::map<std::string,Level*>& levelMap )
{

    // open the file
    std::ifstream file( fileName.c_str() );
    if( !file.is_open() )
        throw Exception( "[CollectionParser::parse] attempt to open collection file failed" );

    // TODO determine file format

    // parse SOK
    this->parseSOK( file, levelMap );
}

// --------------------------------------------------------------
void CollectionParser::parseSOK( std::ifstream& file, std::map<std::string, Level*>& levelMap )
{
    Uint32 successiveColons = 0;
    Uint8 state = 0; // 0 - file header, 1, create new level, 2 - read level data, 3 - meta data
    Uint32 levelPosY;

    Level* activeLevel = NULL;

    std::string levelName("");
    std::string possibleLevelName("");
    std::string inBuf("");
    std::map<std::string,std::string> headerData;
    while( !file.eof() )
    {
        if( inBuf.size() > 1 ) possibleLevelName = inBuf;
        std::getline( file, inBuf );
        for( size_t pos = 0; pos != inBuf.size(); ++pos )
        {

            // count successive colons
            if( inBuf[pos] == ':' ) ++successiveColons; else successiveColons = 0;

            // detect level data
            bool levelDataDetected = false;
            {
                Uint32 pos2 = 0;
                while( pos2 != inBuf.size() && (inBuf[pos2] == 32 || inBuf[pos2] == 9 ) ) ++pos2; // seek to first non-space character
                if( pos2 < inBuf.size() && pos2 < inBuf.size()-1 ) // first and last must be either box on goal or wall
                {
                    if( inBuf[pos2] == '#' || inBuf[pos2] == '*' || inBuf[pos2] == 'B' )
                        if( inBuf[inBuf.size()-1] == '#' || inBuf[inBuf.size()-1] == '*' || inBuf[inBuf.size()-1] == 'B' )
                            levelDataDetected = true;
                }
            }

            // detect comment
            if( successiveColons == 2 )
            {
                successiveColons = 0;
                break;
            }

            switch( state )
            {

                // file header
                case 0 :

                    // detect key-value entry
                    if( successiveColons == 1 )
                    {
                        size_t pos2 = pos; // scan back until a space or tab is found
                        while( inBuf[pos2] != 32 && inBuf[pos2] != 9 && pos2 != 0 ) --pos2;

                        size_t pos3 = pos+1; // scan forward until comment starts, or end of line is found
                        while( pos3 != inBuf.size() && inBuf[pos3] != ':' ) ++pos3;

                        if( pos2 != pos && pos3 != pos+1 )
                            if( headerData.find(inBuf.substr(pos2, pos-pos2)) == headerData.end() )
                                headerData[inBuf.substr(pos2, pos-pos2)] = inBuf.substr(pos+1, pos3-pos);

                        possibleLevelName = ""; // cannot be a level name
                    }

                    // level data was detected
                    if( levelDataDetected )
                    {
                        state = 1;
                        if( possibleLevelName.size() > 0 && levelName.size() == 0 ) levelName = possibleLevelName;
                    }

                break;

                // create new level
                case 1:

                    // add current level to map of levels
                    // auto generate level name if it doesn't exist
                    if( activeLevel )
                    {
                        this->registerLevel( activeLevel, levelName, levelMap );
                    }

                    // prepare new level
                    activeLevel = new Level();
                    state = 2;
                    levelPosY = 0;
                    if( possibleLevelName.size() > 0 ) levelName = possibleLevelName; else levelName = "";

                // purposefully commented, so case 2 is executed this pass
                // break;

                // read level data
                case 2 :
                {

                    possibleLevelName = ""; // cannot be level name

                    // end of level data
                    if( !levelDataDetected )
                    {
                        state = 3;
                        break;
                    }

                    // decompress and add level data
                    RLE rle;
                    rle.decompress( inBuf );
                    for( size_t pos2 = 0; pos2 != inBuf.size(); ++pos2 )
                        activeLevel->insertTile( static_cast<Uint32>(pos2), levelPosY, inBuf[pos2] );
                    ++levelPosY;

                    break;
                }

                // meta data
                case 3 :

                    // detect key-value entry
                    if( successiveColons == 1 )
                    {
                        size_t pos2 = pos; // scan back until a space or tab is found
                        while( inBuf[pos2] != 32 && inBuf[pos2] != 9 && pos2 != 0 ) --pos2;

                        size_t pos3 = pos+1; // scan forward until comment starts, or end of line is found
                        while( pos3 != inBuf.size() && inBuf[pos3] != ':' ) ++pos3;

                        if( pos2 != pos && pos3 != pos+1 )
                            activeLevel->addMetaData( inBuf.substr(pos2, pos-pos2), inBuf.substr(pos+1, pos3-pos) );

                        possibleLevelName = ""; // cannot be a level name
                    }

                    // if more than 2 successive characters match level data,
                    // it can be assumed this is a level
                    if( levelDataDetected )
                    {
                        state = 1;
                        if( possibleLevelName.size() > 0  && levelName.size() == 0 ) levelName = possibleLevelName;
                    }

                break;
                default: break;
            }

            // if reading level data, instantly exit
            if( state == 2 ) break;

        }
    }

    // add current level to map of levels
    // auto generate level name if it doesn't exist
    if( activeLevel )
    {
        this->registerLevel( activeLevel, levelName, levelMap );
    }

}

// --------------------------------------------------------------
void CollectionParser::registerLevel( Level* level, std::string& levelName, std::map<std::string, Level*>& levelMap )
{
    std::stringstream ss;
    if( levelName.size() == 0 )
    {
        Uint32 i = 1;
        do{
            ss.clear();
            ss.str("");
            ss << "Level #";
            ss << i;
            ++i;
        }while( levelMap.find(ss.str()) != levelMap.end() );
        levelName = ss.str();
    }
    levelMap[levelName] = level;
    std::cout << "registered level " << levelName << std::endl;
}

} // namespace Sokoban
