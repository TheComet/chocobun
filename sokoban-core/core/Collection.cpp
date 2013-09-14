// --------------------------------------------------------------
// Collection
// --------------------------------------------------------------

// --------------------------------------------------------------
// include files

#include <core/Collection.hpp>
#include <core/CollectionParser.hpp>

#include <iostream>
#include <core/Level.hpp>

namespace Sokoban {

// --------------------------------------------------------------
Collection::Collection( const std::string& fileName ) :
    m_FileName( fileName )
{
}

// --------------------------------------------------------------
Collection::~Collection( void )
{
}

// --------------------------------------------------------------
void Collection::initialise( void )
{
    CollectionParser cp;
    cp.parse( m_FileName, m_LevelMap );
    for( std::map<std::string, Level*>::iterator it = m_LevelMap.begin(); it != m_LevelMap.end(); ++it )
    {
        std::cout << "level: " << it->first << std::endl;
        it->second->drawLevel();
        std::cout << std::endl;
    }
}

// --------------------------------------------------------------
void Collection::deinitialise( void )
{
}

// --------------------------------------------------------------
void Collection::setName( const std::string& name )
{
    m_CollectionName = name;
}

} // namespace Sokoban
