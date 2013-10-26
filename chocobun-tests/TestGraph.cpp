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
#include <ChocobunGraph.hxx>
#include <exception>

using namespace Chocobun;

// --------------------------------------------------------------
// define test fixtures

#define TEST_CASE_NAME TestGraph
#define TEST_CASE_OBJECT Graph<char>
#define TEST_CASE_NODE GraphNode<char>

TEST( TEST_CASE_NAME, AllNodesAreDeleted )
{
    TEST_CASE_OBJECT test;
    ASSERT_EQ( 0, test.getNodeCount() );
    test.addNode();
    test.addNode();
    test.addNode();
    ASSERT_EQ( 3, test.getNodeCount() );
    test.removeAllNodes();
    ASSERT_EQ( 0, test.getNodeCount() );
}

TEST( TEST_CASE_NAME, SingleNodesAreDeleted )
{
    TEST_CASE_OBJECT test;
    TEST_CASE_NODE* node1 = test.addNode();
    TEST_CASE_NODE* node2 = test.addNode();
    TEST_CASE_NODE* node3 = test.addNode();
    test.removeNode( node2 );
    ASSERT_EQ( 2, test.getNodeCount() );
    ASSERT_EQ( node1, test.getNodePtr(0) );
    ASSERT_EQ( node3, test.getNodePtr(1) );
}

TEST( TEST_CASE_NAME, ReturnsCorrectNodes )
{
    TEST_CASE_OBJECT test;
    TEST_CASE_NODE* node1 = test.addNode();
    TEST_CASE_NODE* node2 = test.addNode();
    ASSERT_EQ( node1, test.getNodePtr(0) );
    ASSERT_EQ( node2, test.getNodePtr(1) );
    ASSERT_EQ( node1, &test.getNode(0) );
    ASSERT_EQ( node2, &test.getNode(1) );
}
