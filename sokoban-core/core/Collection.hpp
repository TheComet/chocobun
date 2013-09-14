// --------------------------------------------------------------
// Collection
// --------------------------------------------------------------

#ifndef __SOKOBAN_CORE_COLLECTION_HPP__
#define __SOKOBAN_CORE_COLLECTION_HPP__

// --------------------------------------------------------------
// include files

#include <map>
#include <string>

namespace Sokoban {

// --------------------------------------------------------------
// forward declarations

class Level;

/*!
 * @brief Holds a collection of levels which can be read from a file
 */
class Collection
{
public:

    /*!
     * @brief Constructs a collection from a given file
     *
     * @param fileName The file to read the collections from
     *
     * @remarks This does not actually load the file, it only stores
     * the file name internally until the initialise method is called
     */
    Collection( const std::string& fileName );

    /*!
     * @brief Destructor
     */
    ~Collection( void );

    /*!
     * @brief Initialises the collection
     *
     * Will parse the file specified in the constructor and load all
     * levels into memory
     */
    void initialise( void );

    /*!
     * @brief De-initialises the collection, freeing up all memory
     */
    void deinitialise( void );

    /*!
     * @brief Sets the name of this collection
     *
     * @param name The name to set
     */
    void setName( const std::string& name );

private:

    std::string m_FileName;
    std::string m_CollectionName;
    std::map<std::string, Level*> m_LevelMap;
};

} // namespace Sokoban

#endif // __SOKOBAN_CORE_COLLECTION_HPP__
