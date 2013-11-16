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
// TestGraphNode_WithoutCoordinates.cpp
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
#define TEST_CASE_OBJECT GraphNode<double,int,char>

TEST( TEST_CASE_NAME, CoordinatesInConstructor )
{
    TEST_CASE_OBJECT test(6.0);
    ASSERT_EQ( 6.0, test.getCoordinate() );
}

TEST( TEST_CASE_NAME, CoordinatesAndDataInConstructor )
{
    TEST_CASE_OBJECT test( 6.0, 10 );
    ASSERT_EQ( 6.0, test.getCoordinate() );
    ASSERT_EQ( 10, test.getData() );
}

TEST( TEST_CASE_NAME, SetAndGetCoordinates )
{
    TEST_CASE_OBJECT test;
    test.setCoordinate(6);
    ASSERT_EQ( 6, test.getCoordinate() );
}
