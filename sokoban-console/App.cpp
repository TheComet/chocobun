/*
 * This file is part of Sokoban.
 *
 * Sokoban is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Sokoban is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Sokoban.  If not, see <http://www.gnu.org/licenses/>.
 */

// --------------------------------------------------------------
// App
// --------------------------------------------------------------

// --------------------------------------------------------------
// include files

#include <App.hpp>
#include <core/Collection.hpp>

#include <iostream>
#include <fstream>

// --------------------------------------------------------------
// constructor
App::App( void ) :
    m_Collection(0)
{
}

// --------------------------------------------------------------
// destructor
App::~App( void )
{
    if( m_Collection ) delete m_Collection;
}

// --------------------------------------------------------------
void App::go( void )
{

    // welcome message
    std::cout << "Welcome to Sokoban!" << std::endl;
    this->displayHelp( "help" );

    bool shutdown = false;
    while( !shutdown )
    {

        // get command
        std::string input;
        std::getline( std::cin, input );

        // switch/case block
        for(;;)
        {

            // split into argument list
            std::vector<std::string> argList;
            std::vector<std::string> optionList;
            {
                input.append(" ");
                size_t pos = 0;
                size_t pos2 = 0;
                bool parenthesisOpen = false;
                do
                {

                    // open and close parenthesis
                    if( input.at(pos2) == '"' )
                    {
                        parenthesisOpen = 1-parenthesisOpen;
                        input.erase(pos2,1);
                    }

                    // don't process anything if parenthesis are open
                    if( !parenthesisOpen )
                    {

                        // split spaces
                        if( input.at(pos2) == ' ' )
                        {
                            argList.push_back( input.substr(pos, pos2-pos) );
                            pos = pos2+1;
                        }

                        // double dash option
                        while( input.substr(pos2,3) == " --" )
                        {
                            pos2 = input.find_first_of(" ",pos2+1);
                            optionList.push_back( input.substr(pos,pos2-pos) );
                            pos = pos2+1;
                        }

                        // single dash options
                        while( input.substr(pos2,2) == " -" )
                        {

                            pos2 += 2;
                            if( pos2 == input.size() || input.at(pos2) == ' ' )
                            {
                                std::cout << "Error: Unfinished option" << std::endl;
                                argList.clear();
                                break;
                            }
                            while( pos2 != input.size() )
                            {
                                if( input.at(pos2) == ' ' ) break;
                                optionList.push_back( input.substr(pos2,1) );
                                ++pos2;
                            }
                            pos = pos2+1;

                        }
                    }

                    ++pos2;
                }while( pos2 != input.size() );
            }
            if( argList.size() == 0 ) break;

            // help command
            if( argList[0].compare("help") == 0 )
            {
                this->displayHelp( argList.at( argList.size()-1 ) );
                break;
            }

            // collection command
            if( argList[0].compare("collection") == 0)
            {

                // collect options
                bool list = false;
                bool open = false;
                bool close = false;
                std::vector<std::string>::iterator it = optionList.begin();
                for( ; it != optionList.end(); ++it )
                {
                    if( it->compare("l") == 0 || it->compare("--list") == 0 ){ list = true; continue; }
                    if( it->compare("o") == 0 || it->compare("--open") == 0 ){ open = true; continue; }
                    if( it->compare("c") == 0 || it->compare("--close") == 0 ){ close = true; continue; }
                    std::cout << "Error: Unkown option \"" << *it << "\"" << std::endl;
                    break;
                }
                if( it != optionList.end() ) break;

                // list collection
                if( list );

                // open collection
                if( open )
                {
                    std::string fileName = "../../collections/" + argList.at( argList.size()-1 );
                    std::ifstream checkFile( fileName.c_str() );
                    if( !checkFile )
                    {
                        std::cout << "Error: Collection \"" << fileName << "\" not found." << std::endl;
                    }else
                    {
                        checkFile.close();
                        if( m_Collection )
                            delete m_Collection;
                        m_Collection = new Sokoban::Collection( fileName );
                        m_Collection->initialise();
                        std::cout << "Successfully opened collection \"" << fileName << "\"" << std::endl;
                    }
                }

                // close collection
                if( close )
                {
                    if( m_Collection )
                    {
                        delete m_Collection;
                        m_Collection = 0;
                        std::cout << "Collection closed." << std::endl;
                    }else
                    {
                        std::cout << "No collection open." << std::endl;
                    }
                }

                break;
            }

            // level command
            if( argList[0].compare("level") == 0 )
            {

                // level options
                bool list = false;
                bool open = false;
                bool close = false;
                bool reset = false;
                std::vector<std::string>::iterator it = optionList.begin();
                for( ; it != optionList.end(); ++it )
                {
                    if( it->compare("l") == 0 || it->compare("--list") == 0 ){ list=true; continue; }
                    if( it->compare("o") == 0 || it->compare("--open") == 0 ){ open=true; continue; }
                    if( it->compare("c") == 0 || it->compare("--close") == 0 ){ close=true; continue; }
                    if( it->compare("r") == 0 || it->compare("--reset") == 0 ){ reset=true; continue; }
                    std::cout << "Error: Unkown option \"" << *it << "\"" << std::endl;
                    break;
                }
                if( it != optionList.end() ) break;

                // collection must be open
                if( !m_Collection )
                {
                    std::cout << "Error: You haven't opened a collection yet." << std::endl;
                    break;
                }

                // list levels
                if( list )
                {
                    m_Collection->streamLevelNames( std::cout );
                }

                // open level
                if( open )
                {
                    if( m_Collection->setActiveLevel( argList.at( argList.size()-1 ) ) )
                        std::cout << "Opened level \"" << argList.at( argList.size()-1 ) << std::endl;
                    else
                        std::cout << "Error: Level \"" << argList.at( argList.size()-1 ) << "\" does not exist" << std::endl;
                }

                break;
            }

            // exit program
            if( argList[0].compare("quit") == 0 )
            {
                shutdown = true;
                break;
            }

            // default
            std::cout << "Error: Unknown command \"" << argList[0] << "\"" << std::endl;
            break;
        }

    }
}

// --------------------------------------------------------------
bool App::displayHelp( const std::string& cmd )
{
    bool helped = false;
    std::cout << std::endl;
    if( cmd.compare("help") == 0 )
    {
        std::cout << " help                   displays this message" << std::endl;
        helped = true;
    }
    if( cmd.compare("quit") == 0 || cmd.compare("help") == 0 )
    {
        std::cout << " quit                   saves and quits the game" << std::endl;
        helped = true;
    }
    if( cmd.compare("collection") == 0 || cmd.compare("help") == 0 )
    {
        std::cout << " collection [OPTIONS]" << std::endl;
        std::cout << "     -l, --list         lists collections ready to load" << std::endl;
        std::cout << "     -o, --open         opens the specified collection" << std::endl;
        std::cout << "     -c, --close        closes the current collection" << std::endl;
        helped = true;
    }
    if( cmd.compare("level") == 0 || cmd.compare("help") == 0 )
    {
        std::cout << " level [OPTIONS]" << std::endl;
        std::cout << "     -l, --list         lists levels ready to load" << std::endl;
        std::cout << "     -o, --open         opens the specified level" << std::endl;
        std::cout << "     -c, --close        closes the current level" << std::endl;
        std::cout << "     -r, --reset        resets the level" << std::endl;
        helped = true;
    }
    if( cmd.compare("move") == 0 || cmd.compare("help") == 0 )
    {
        std::cout << "Type the letters 'u', 'd', 'l', or 'r' to move around in a level." << std::endl;
        std::cout << "Type the letter 'z' to undo a move" << std::endl;
        std::cout << "You may chain together as many as required" << std::endl;
        helped = true;
    }
    std::cout << std::endl;
    if( !helped)
        std::cout << "Error: Unknown help topic \"" << cmd << "\"" << std::endl;
}
