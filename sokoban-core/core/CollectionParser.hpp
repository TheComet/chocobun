// --------------------------------------------------------------
// Collection Parser
// --------------------------------------------------------------

#ifndef __SOKOBAN_CORE_COLLECTION_PARSER_HPP__
#define __SOKOBAN_CORE_COLLECTION_PARSER_HPP__

// --------------------------------------------------------------
// include files

#include <map>
#include <string>

namespace Sokoban {

// --------------------------------------------------------------
// forward declarations

class Level;

/*!
 * @brief Parses a collection and loads all levels into an internal format
 */
class CollectionParser
{
public:

    /*!
     * @brief Constructor
     */
    CollectionParser( void );

    /*!
     * @brief Destructor
     */
    ~CollectionParser( void );

    /*!
     * @brief Parses a collection file and writes into a map of levels
     */
    void parse( const std::string& fileName, std::map<std::string, Level*>& levelMap );

private:

    /*!
     * @brief Universal .SOK format parser
     *
     * See http://sokobano.de/wiki/index.php?title=Sok_format for more information
     */
    void parseSOK( std::ifstream& file, std::map<std::string, Level*>& levelMap );

    /*!
     * @brief Registers a level to a level map
     */
    void registerLevel( Level* level, std::string& levelName, std::map<std::string, Level*>& levelMap );

};

} // namespace Sokoban

#endif // __SOKOBAN_CORE_COLLECTION_PARSER_HPP__
