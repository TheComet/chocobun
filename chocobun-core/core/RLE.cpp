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
// RLE.cpp
// --------------------------------------------------------------

// --------------------------------------------------------------
// include files

#include <sstream>
#include <core/RLE.hpp>
#include <core/Config.hpp>

namespace Chocobun {

// --------------------------------------------------------------
RLE::RLE( void )
{
}

// --------------------------------------------------------------
RLE::~RLE( void )
{
}

// --------------------------------------------------------------
void RLE::compress( std::string& str )
{

    // loops through all characters in the string
    std::string ret("");
    size_t pos = 0;
    while( pos != str.size() )
    {

        // loops until the current character doesn't match proceeding characters
        size_t pos2 = pos+1;
        while( pos2 != str.size() && str[pos] == str[pos2] ) ++pos2;

        // if more than one successive characters were found, apply RLE format
        if( pos2 != pos+1 )
        {
            std::stringstream ss;
            ss << (pos2-pos);
            ret.append( ss.str() );
        }
        ret.push_back( str[pos] );
        pos = pos2;
    }
    str = ret;
}

// --------------------------------------------------------------
void RLE::multiPassCompress( std::string& str )
{

    // the same compression algorithm is performed twice,
    // one time factoring from the outside in and the other
    // time factoring from the inside out. The two are compared
    // and the best result is returned.
    std::string cp;
    std::string method1( str );
    std::string method2;

    // the compare size is the number of characters to compare with the
    // rest of the string to find matching patterns
    // NOTE: A "ping-pong" pattern has been implemented to avoid
    // useless copying of string objects between each other
    for( size_t compareSize = 1; compareSize < str.size()/2; ++compareSize )
    {
        cp.clear();
        this->multPassCompress_pass( compareSize, method1, cp ); ++compareSize;
        method1.clear();
        this->multPassCompress_pass( compareSize, cp, method1 );
    }
    for( size_t compareSize = str.size()/2; compareSize > 0; --compareSize )
    {
        method2.clear();
        this->multPassCompress_pass( compareSize, str, method2 );
        if(!(--compareSize))
        {
            str = method2;
            break;
        }
        str.clear();
        this->multPassCompress_pass( compareSize, method2, str );
    }

    // compare length to determine which one was more successful
    if( method1.size() < str.size() ) str = method1;
}

// --------------------------------------------------------------
void RLE::multPassCompress_pass( const size_t& compareSize, std::string& input, std::string& output )
{

    // loops through all characters in the string witha step size
    // of the compare size
    size_t pos = 0;
    while( pos < input.size() )
    {

        // the compare string
        std::string compare = input.substr( pos, compareSize );

        // loops until the compare pattern doesn't repeat any more
        size_t pos2 = pos+compareSize;
        while( pos2 < input.size() && input.substr(pos2, compareSize).compare(compare) == 0 ) pos2 += compareSize;

        // if a pattern was found, apply RLE formatting
        if( pos2 != pos+compareSize )
        {
            std::stringstream ss;
            ss << ((pos2-pos) / compareSize);
            output.append( ss.str() );
            if( compareSize != 1 )
            {
                output.push_back( '(' );
                output.append( compare );
                output.push_back( ')' );
            }else
                output.append( compare );
        }

        // if no pattern was found, simply append the compare pattern
        else
            output.append( compare );

        pos = pos2;
    }
}

// --------------------------------------------------------------
size_t RLE::decompress( std::string& str )
{
    std::string ret("");
    size_t pos = 0;
    while( pos < str.size() )
    {

        // closing parenthesis
        if( str[pos] == ')' ) break;

        // get expansion
        Chocobun::Int32 expansionCount = 0, digit = 1;
        while( str[pos] > 47 && str[pos] < 58 )
        {
            expansionCount *= digit;
            expansionCount += static_cast<Chocobun::Int32>( str[pos]-48 );
            digit *= 10;
            ++pos;
        }
        if( digit == 1 ) expansionCount = 1;

        // get string to expand
        std::string expansionString = "";
        if( str[pos] == '(' )
        {
            expansionString = str.substr(pos+1); // +1 to skip opening parenthesis
            pos += decompress( expansionString );
        }
        else
            expansionString.push_back( str[pos] );

        // expand
        for( Chocobun::Int32 i = 0; i != expansionCount; ++i )
            ret.append( expansionString );
        ++pos;
    }
    str = ret;
    return pos+1; // +1 to skip closing parenthesis
}

} // namespace Chocobun
