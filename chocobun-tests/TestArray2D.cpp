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
// TestArray2D.cpp
// --------------------------------------------------------------

// --------------------------------------------------------------
// include files

#include <gtest/gtest.h>
#include <core/Array2D.hpp>

// --------------------------------------------------------------
// define test fixtures

#define TEST_CASE_NAME TestArray2D
#define TEST_CASE_OBJECT Chocobun::Array2D<char>

TEST( TEST_CASE_NAME, testingShit )
{
    TEST_CASE_OBJECT test( '#' );
    test.resize(5,5);
    EXPECT_EQ( 5, test.sizeX() );
}
