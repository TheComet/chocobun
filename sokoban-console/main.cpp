// Sokoban
// TheComet

// --------------------------------------------------------------
// include files

#include <App.hpp>
#include <exception>
#include <iostream>

// --------------------------------------------------------------
// main entry point
int main( int argc, char** argv )
{

    App* theApp = new App();
    try {
        theApp->go();
    }catch( const std::exception& e ) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    delete theApp;

    return 0;
}
