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

#ifndef __RLE_HPP__
#define __RLE_HPP__

// ------------------------------------------------------------
// include files

#include <string>

namespace Chocobun {

/*!
 * @brief Simple RLE compression and decompression class
 *
 * @author Alex Murray (TheComet)
 *
 * <b>Run-length encoding (RLE)</b> is a very simple form of data compression
 * in which <i>runs</i> of data (that is, sequences in which the same data
 * value occurs in many consecutive data elements) are stored as a
 * single data value and count, rather than as the original run. This
 * is most useful on data that contains many such runs: for example,
 * simple graphic images such as icons, line drawings, and animations.
 * It is not useful with files that don't have many runs as it could
 * greatly increase the file size.
 *
 * <b>This implementationi supports two forms of RLE compression.</b>
 *
 * <b>Standard Compression</b> performs one pass on the data provided
 * and factors it accordingly. For example:
 * @code ####$$####$$####$$####$$ @endcode
 * becomes:
 * @code 4#2$4#2$4#2$4#2$ @endcode
 *
 * <b>Multi-pass Compression</b> performs as many passes as is required
 * to fully factor the string as far as possible. For example:
 * @code ####$$####$$####$$####$$ @endcode
 * becomes:
 * @code 4(4#2$) @endcode
 *
 */
class RLE
{
public:

    /*!
     * @brief Constructor
     */
    RLE( void );

    /*!
     * @brief Destructor
     */
    ~RLE( void );

    /*!
     * @brief Standard RLE compression
     *
     * Performs one pass on the data provided and factors it accordingly. For example:
     * @code ####$$####$$####$$####$$ @endcode
     * becomes:
     * @code 4#2$4#2$4#2$4#2$ @endcode
     *
     * @param str The string to compress
     */
    void compress( std::string& str );

    /*!
     * @brief Multi-pass RLE compression using parenthesis
     *
     * Performs as many passes as is required to fully factor the string
     * as far as possible. For example:
     * @code ####$$####$$####$$####$$ @endcode
     * becomes:
     * @code 4(4#2$) @endcode
     *
     * @param str The string to compress
     */
    void multiPassCompress( std::string& str );

    /*!
     * @brief RLE Decompression
     * @note Supports multi-pass and standard compression
     *
     * @param str The string to decompress
     * @return Returns a size_t position relative to the string's beginning
     * where the last refactor occurred. You may ignore this and simply call
     * the method without catching the return value; it's used internally.
     */
    size_t decompress( std::string& str );

private:

    /*!
     * @brief Passes an entire string, factoring out sections with the length of compareSize
     *
     * @param compareSize The length of the sections to factor out
     * @param input The input string
     * @param output The output string
     *
     * @note This is used internally by the multi-pass compression method
     */
    void multPassCompress_pass( const size_t& compareSize, std::string& input, std::string& output );
};

} // namespace Chocobun

#endif // __RLE_HPP__
