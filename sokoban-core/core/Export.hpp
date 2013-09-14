// --------------------------------------------------------------
// define export macros
// --------------------------------------------------------------

#ifndef __SOKOBAN_CORE_EXPORT_HPP__
#   define __SOKOBAN_CORE_EXPORT_HPP__

    // headers
#   include <core/Config.hpp>

#   if defined(SOKOBAN_CORE_DYNAMIC)
#       define SOKOBAN_CORE_API SOKOBAN_CORE_EXPORT
#   else
#       define SOKOBAN_CORE_API SOKOBAN_CORE_IMPORT
#   endif

#endif // __SOKOBAN_CORE_EXPORT_HPP__
