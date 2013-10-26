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

TEST( TEST_CASE_NAME, CopiesAndLinksCorrectlyOnAssignment )
{

    // build a small graph
    TEST_CASE_OBJECT test1;
    TEST_CASE_OBJECT test2;
    TEST_CASE_NODE* node1 = test1.addNode();
    TEST_CASE_NODE* node2 = test1.addNode();
    TEST_CASE_NODE* node3 = test1.addNode();
    node1->link( node2 );
    node2->link( node3 );

    // this is what is being tested
    test2 = test1;

    // test links
    ASSERT_EQ( 1, test2.getNode(0).getLinkCount() );
    ASSERT_EQ( 2, test2.getNode(1).getLinkCount() );
    ASSERT_EQ( 1, test2.getNode(2).getLinkCount() );
    ASSERT_EQ( test2.getNodePtr(0), test2.getNode(1).getLinkedNode(0) );
    ASSERT_EQ( test2.getNodePtr(1), test2.getNode(0).getLinkedNode(0) );
    ASSERT_EQ( test2.getNodePtr(1), test2.getNode(2).getLinkedNode(0) );
    ASSERT_EQ( test2.getNodePtr(2), test2.getNode(1).getLinkedNode(1) );
}
