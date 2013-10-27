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
// TestTileManipulator.cpp
// --------------------------------------------------------------

#include <gmock/gmock.h>
#include <ChocobunTileManipulator.hxx>

using namespace Chocobun;

using ::testing::_;
using ::testing::Return;

// --------------------------------------------------------------
// define test fixtures

#define TEST_CASE_NAME TestTileManipulator
#define GRAPH_DATA_CONTENT int
#define GRAPH_POSITION int
#define GRAPH_OBJECT DummyGraph<GRAPH_DATA_CONTENT>
#define TEST_CASE_OBJECT TileManipulator<GRAPH_OBJECT,GRAPH_POSITION>

// tile manipulator requires a graph class before it can be instantiated
// said class requires a type definition "Data" to be defined
template <class T>
class DummyGraph
{
public:
    typedef T Data;
};

// tile manipulator can register listener classes
// define a simple listener class for checking whether the methods
// are properly called
class MockListener : public TEST_CASE_OBJECT::Listener
{
public:
    MOCK_METHOD3( onMoveTile, void(const GRAPH_OBJECT&, const GRAPH_POSITION&, const GRAPH_POSITION&) );
    MOCK_METHOD2( onSetTile, void(const GRAPH_OBJECT&, const GRAPH_POSITION&) );
};

// define mock class for tile manipulator, since most methods
// don't actually do anything without being implemented by a derived
// class
class MockTestCaseObject : public TEST_CASE_OBJECT
{
public:
    MOCK_METHOD3( _moveTile, bool(GRAPH_OBJECT&, const GRAPH_POSITION&, const GRAPH_POSITION&) );
    MOCK_METHOD3( _setTile, bool(GRAPH_OBJECT&, const GRAPH_POSITION&, const GRAPH_POSITION&) );
};

// Test whether derived class' move tile implementation is called
TEST( TEST_CASE_NAME, MoveTileImplementationIsCalled )
{
    MockTestCaseObject test;
    GRAPH_OBJECT graph;
    EXPECT_CALL( test, _moveTile(_,5,8) ); // these values are random and have no significance
    test.moveTile(graph, 5, 8 );
}

// Test whether derived class' set tile implementation is called
TEST( TEST_CASE_NAME, SetTileImplementationIsCalled )
{
    MockTestCaseObject test;
    GRAPH_OBJECT graph;
    EXPECT_CALL( test, _setTile(_,5,8) ); // these values are random and have no significance
    test.setTile( graph, 5, 8 );
}

// Test whether listeners are informed about tile movements
TEST( TEST_CASE_NAME, ListenersAreInformedAboutTileMoves )
{
    MockTestCaseObject test;
    GRAPH_OBJECT graph;
    MockListener listener1;
    MockListener listener2;
    test.addListener( &listener1 );
    test.addListener( &listener2 );

    // configure move tile implementation to return true
    ON_CALL( test, _moveTile(_,_,_) )
        .WillByDefault( Return(true) );

    EXPECT_CALL( test, _moveTile(_,4,7) );
    EXPECT_CALL( listener1, onMoveTile(_,4,7) );
    EXPECT_CALL( listener2, onMoveTile(_,4,7) );

    test.moveTile( graph, 4, 7 );
}

// Test whether listeners are informed about tiles being set
TEST( TEST_CASE_NAME, ListenersAreInformedAboutTilesBeingSet )
{
    MockTestCaseObject test;
    GRAPH_OBJECT graph;
    MockListener listener1;
    MockListener listener2;
    test.addListener( &listener1 );
    test.addListener( &listener2 );

    // configure set tile implementation to return true
    ON_CALL( test, _setTile(_,_,_) )
        .WillByDefault( Return(true) );

    EXPECT_CALL( test, _setTile(_,4,7) );
    EXPECT_CALL( listener1, onSetTile(_,4) );
    EXPECT_CALL( listener2, onSetTile(_,4) );

    test.setTile( graph, 4, 7 );
}

// Test whether listeners aren't informed if false is returned in
// the implementation method
TEST( TEST_CASE_NAME, ListenersArentInformedIfFalseIsReturned )
{
    MockTestCaseObject test;
    GRAPH_OBJECT graph;
    MockListener listener1;
    MockListener listener2;
    test.addListener( &listener1 );
    test.addListener( &listener2 );

    // set tile and move tile implementations should return false by default
    // so listeners won't be informed

    EXPECT_CALL( test, _moveTile(_,5,7) );
    EXPECT_CALL( test, _setTile(_,4,7) );
    EXPECT_CALL( listener1, onMoveTile(_,5,7) )
        .Times(0);
    EXPECT_CALL( listener1, onSetTile(_,4) )
        .Times(0);
    EXPECT_CALL( listener2, onMoveTile(_,5,7) )
        .Times(0);
    EXPECT_CALL( listener2, onSetTile(_,4) )
        .Times(0);

    test.moveTile( graph, 5, 7 );
    test.setTile( graph, 4, 7 );
}

// Test whether listeners can be removed
TEST( TEST_CASE_NAME, ListenersCanBeRemoved )
{
    MockTestCaseObject test;
    GRAPH_OBJECT graph;
    MockListener listener1;
    MockListener listener2;
    test.addListener( &listener1 );
    test.addListener( &listener2 );
    test.removeListener( &listener1 );

    // configure set tile and move tile implementations to return true
    // so listeners are informed
    ON_CALL( test, _setTile(_,_,_) )
        .WillByDefault( Return(true) );
    ON_CALL( test, _moveTile(_,_,_) )
        .WillByDefault( Return(true) );

    EXPECT_CALL( test, _moveTile(_,5,7) );
    EXPECT_CALL( test, _setTile(_,4,7) );
    EXPECT_CALL( listener1, onMoveTile(_,5,7) )
        .Times(0);
    EXPECT_CALL( listener1, onSetTile(_,4) )
        .Times(0);
    EXPECT_CALL( listener2, onMoveTile(_,5,7) );
    EXPECT_CALL( listener2, onSetTile(_,4) );

    test.moveTile( graph, 5, 7 );
    test.setTile( graph, 4, 7 );
}
