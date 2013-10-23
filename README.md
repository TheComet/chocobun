# Chocobun

Chocobun is a cross-platform Sokoban engine. It is specifically 
being designed to be able to run as a back-end for any sokoban
game.

## Features and progress

* Importers/Exporters
    + (done) .SOK file importer/exporter
    + ( 90%) SCL markup language importer/exporter
    + (  0%) SBML markup language importer/exporter
    + (  0%) XSB file importer/exporter
* Player dynamics
    + (done) Basic movement of the player on levels
    + (done) Undo/Redo moves
    + (  0%) Move the player using a path-finder
* Level dynamics
    + ( 20%) Validate levels, make sure they are solvable
    + (  0%) Level solver
* Misc
    + (  0%) Generic A* path-finder

## Compiling Chocobun

You need to have premake version 4.0 or later installed in
order to generate build files. You can download it here:

http://industriousone.com/premake

You can generate the required build files by navigating to the
project's root directory and running `premake <generator>`.
After that you may build the project as usual.

Here is an example of building it using GNU makefiles.

    # generate GNU makefiles
    $ premake gmake

    # compile
    $ make

## Running Chocobun

To simply answer this, you can't run it. Why? Because it's an
*engine*. It's designed to function as a back-end for a game.

With that said, there is a simple developer 'test' project
included with Chocobun: A console front-end. It links against
Chocobun, and should serve as an example of how to interface
the engine.

### Running chocobun-console

On Windows, you can simply double-click on the executable
in bin/debug/chocobun-console.exe

On POSIX systems, the dynamic libs need to be explicitely
linked. This involves some terminal interaction:

    # navigate to the executable
    $ cd bin/debug

    # the chocobun engine is built to bin/debug, so add
    # it to the library path
    $ export LD_LIBRARY_PATH=.

    # now we can run it
    $ ./chocobun-console
