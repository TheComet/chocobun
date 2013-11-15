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
// TestGraphNode.cpp
// --------------------------------------------------------------

// --------------------------------------------------------------
// include files

#include <gmock/gmock.h>
#include <ChocobunGraphNode.hxx>
#include <exception>

using namespace Chocobun;

// --------------------------------------------------------------
// define test fixtures

#define TEST_CASE_NAME TestGraphNode
#define TEST_CASE_OBJECT GraphNode<int,int,char>

TEST( TEST_CASE_NAME, ContentIsStored )
{
    TEST_CASE_OBJECT test('a');
    ASSERT_EQ( 'a', test.getData() );
    test.setData( 'b' );
    ASSERT_EQ( 'b', test.getData() );
}

TEST( TEST_CASE_NAME, NodesDoLink )
{
    TEST_CASE_OBJECT test, linkObj1, linkObj2, linkObj3;
    ASSERT_EQ( 0, test.getLinkCount() );
    ASSERT_EQ( 0, linkObj1.getLinkCount() );
    ASSERT_EQ( 0, linkObj2.getLinkCount() );
    ASSERT_EQ( 0, linkObj3.getLinkCount() );

    test.link( &linkObj1, 0 );
    test.link( &linkObj2, 0 );
    test.link( &linkObj3, 0 );
    ASSERT_EQ( 3, test.getLinkCount() );
    ASSERT_EQ( 1, linkObj1.getLinkCount() );
    ASSERT_EQ( 1, linkObj2.getLinkCount() );
    ASSERT_EQ( 1, linkObj3.getLinkCount() );

    ASSERT_EQ( &test, linkObj1.getNodeLink(0).link );
    ASSERT_EQ( &test, linkObj2.getNodeLink(0).link );
    ASSERT_EQ( &test, linkObj3.getNodeLink(0).link );
    ASSERT_EQ( &linkObj1, test.getNodeLink(0).link );
    ASSERT_EQ( &linkObj2, test.getNodeLink(1).link );
    ASSERT_EQ( &linkObj3, test.getNodeLink(2).link );
}

TEST( TEST_CASE_NAME, NodesDoUnlink )
{
    TEST_CASE_OBJECT test, linkObj1, linkObj2, linkObj3;
    test.link( &linkObj1, 0 );
    test.link( &linkObj2, 0 );
    test.link( &linkObj3, 0 );

    test.unlink( &linkObj2 );
    ASSERT_EQ( 2, test.getLinkCount() );
    ASSERT_EQ( 1, linkObj1.getLinkCount() );
    ASSERT_EQ( 0, linkObj2.getLinkCount() );
    ASSERT_EQ( 1, linkObj3.getLinkCount() );
    ASSERT_EQ( &test, linkObj1.getNodeLink(0).link );
    ASSERT_EQ( &test, linkObj3.getNodeLink(0).link );
    ASSERT_EQ( &linkObj1, test.getNodeLink(0).link );
    ASSERT_EQ( &linkObj3, test.getNodeLink(1).link );
}

TEST( TEST_CASE_NAME, NodesDoUnlinkAll )
{
    TEST_CASE_OBJECT test, linkObj1, linkObj2, linkObj3;
    test.link( &linkObj1, 0 );
    test.link( &linkObj2, 0 );
    test.link( &linkObj3, 0 );
    test.unlinkAll();
    ASSERT_EQ( 0, test.getLinkCount() );
    ASSERT_EQ( 0, linkObj1.getLinkCount() );
    ASSERT_EQ( 0, linkObj2.getLinkCount() );
    ASSERT_EQ( 0, linkObj3.getLinkCount() );
}

TEST( TEST_CASE_NAME, NodesLinksStoreMovementCost )
{
    TEST_CASE_OBJECT test, linkObj1, linkObj2;
    test.link( &linkObj1, 3 );
    test.link( &linkObj2, 6 );
    ASSERT_EQ( 3, test.getNodeLink(0).moveCost );
    ASSERT_EQ( 6, test.getNodeLink(1).moveCost );
    ASSERT_EQ( 3, linkObj1.getNodeLink(0).moveCost );
    ASSERT_EQ( 6, linkObj2.getNodeLink(0).moveCost );
}

TEST( TEST_CASE_NAME, CoordinateIsStoredInNodes )
{
    TEST_CASE_OBJECT test;
    test.setCoordinate(6);
    ASSERT_EQ( 6, test.getCoordinate() );
}

TEST( TEST_CASE_NAME, DataIsStoredInNodes )
{
    TEST_CASE_OBJECT test;
    test.setData(6);
    ASSERT_EQ( 6, test.getData() );
}

TEST( TEST_CASE_NAME, NodeLinkIDOutOfRangeException )
{
    TEST_CASE_OBJECT test, linkObj;
    test.link( &linkObj, 0 );
    ASSERT_NO_THROW( test.getNodeLink(0).link );
    ASSERT_THROW( test.getNodeLink(1).link, std::exception );
}
