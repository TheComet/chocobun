// --------------------------------------------------------------
// App
// --------------------------------------------------------------

#ifndef __APP_HPP__
#define __APP_HPP__

// --------------------------------------------------------------
// include files

// --------------------------------------------------------------
// forward declarations

/*!
 * @brief The application object
 */
class App
{
public:

    /*!
     * @brief Constructor
     */
    App( void );

    /*!
     * @brief Destructor
     */
    ~App( void );

    /*!
     * @brief Launches the application
     *
     * @note Will throw std::exception if anything fails
     */
    void go( void );
};

#endif // __APP_HPP__
