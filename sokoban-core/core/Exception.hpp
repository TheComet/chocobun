// --------------------------------------------------------------
// Exception
// --------------------------------------------------------------

#ifndef __SOKOBAN_CORE_EXCEPTION_HPP__
#define __SOKOBAN_CORE_EXCEPTION_HPP__

// --------------------------------------------------------------
// include files

#include <exception>

namespace Sokoban {

/*!
 * @brief Simple exception class used throughout sokoban-core
 */
class Exception :
    public std::exception
{
public:

    /*!
     * @brief Constructor
     *
     * @param message A string for identifying the error that has occured
     */
    Exception( const char* message ) throw() : m_Message(message) {}

    /*!
     * @brief Destructor
     */
    ~Exception( void ) throw() {}

    /*!
     * @brief Gets the message of the error
     * @note Overridden from std::exception's "what()" method
     */
    const char* what( void ) const throw() { return m_Message; }

private:
    const char* m_Message;
};

} // namespace Sokoban

#endif // __SOKOBAN_CORE_EXCEPTION_HPP__
