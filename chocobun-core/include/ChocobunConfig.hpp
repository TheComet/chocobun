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
// Configures prerequisits for this library
// --------------------------------------------------------------

#ifndef __CHOCOBUN_CORE_CONFIG_HPP__
#   define __CHOCOBUN_CORE_CONFIG_HPP__

    // --------------------------------------------------------------
    // Identify the operating system
    // --------------------------------------------------------------

#   if defined(_WIN32) || defined(__WIN32__)
#       define CHOCOBUN_CORE_PLATFORM_WINDOWS
#   elif defined(linux) || defined(__linux)
#       define CHOCOBUN_CORE_PLATFORM_LINUX
#   elif defined(__APPLE__) || defined(MACOSX) || defined(macintosh) || defined(Macintosh)
#       define CHOCOBUN_CORE_PLATFORM_MAC
#   else
#       error This operating system is not supported
#   endif

// --------------------------------------------------------------
// define import/export macros
// --------------------------------------------------------------

#   if defined(CHOCOBUN_CORE_DYNAMIC)
#       if defined(CHOCOBUN_CORE_PLATFORM_WINDOWS)

            // windows compilers need specific (and different) keywords for export and import
#           define CHOCOBUN_CORE_EXPORT __declspec(dllexport)
#           define CHOCOBUN_CORE_IMPORT __declspec(dllimport)

            // disable annoying warnings in MSVC
#           ifdef _MSC_VER
#               pragma warning(disable:4251)    // needs to have dll-interface to be used by clients of class
#               pragma warning(disable:4275)    // non dll-interface class 'OIS::KeyListener' used as base for dll-interface class
#           endif

// linux and mac
#       else
#           if __GNUC__ >= 4

                // GCC 4 has special keywords for showing/hidding symbols,
                // the same keyword is used for both importing and exporting
#               define CHOCOBUN_CORE_EXPORT __attribute__ ((__visibility__ ("default")))
#               define CHOCOBUN_CORE_IMPORT __attribute__ ((__visibility__ ("default")))
#           else

                // GCC < 4 has no mechanism to explicitely hide symbols, everything's exported
#               define CHOCOBUN_CORE_EXPORT
#               define CHOCOBUN_CORE_IMPORT
#           endif
#       endif
#   elif defined(CHOCOBUN_CORE_STATIC)

        // static build doesn't need import/export macros
#       define CHOCOBUN_CORE_EXPORT
#       define CHOCOBUN_CORE_IMPORT
#   else

        // dynamic or static build wasn't defined
#       error Please define CHOCOBUN_CORE_DYNAMIC OR CHOCOBUN_CORE_STATIC
#   endif

namespace Chocobun {

// --------------------------------------------------------------
// define fixed-type sizes
// --------------------------------------------------------------

// All "common" platforms use the same size for char, short and int
// (basically there are 3 types for 3 sizes, so no other match is possible),
// we can use them without doing any kind of check

// 8 bits integer types
typedef signed   char Int8;
typedef unsigned char Uint8;

// 16 bits integer types
typedef signed   short Int16;
typedef unsigned short Uint16;

// 32 bits integer types
typedef signed   int Int32;
typedef unsigned int Uint32;

// 64 bits integer types
#   if defined(_MSC_VER)
typedef signed   __int64 Int64;
typedef unsigned __int64 Uint64;
#   else
typedef signed   long long Int64;
typedef unsigned long long Uint64;
#   endif

} // namespace Chocobun

#endif // __CHOCOBUN_CORE_CONFIG_HPP__
