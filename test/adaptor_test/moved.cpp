// Boost.Range library
//
//  Copyright Neil Groves 2009.
//  Copyright Adam Wulkiewicz 2014.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
//
// For more information, see http://www.boost.org/libs/range/
//
#include <boost/range/adaptor/moved.hpp>

#include <boost/test/test_tools.hpp>
#include <boost/test/unit_test.hpp>

#include <boost/assign.hpp>
#include <boost/range/algorithm_ext.hpp>

#include <algorithm>
#include <list>
#include <set>
#include <vector>

#include "../copymovable.hpp"

namespace boost
{
    template <typename It>
    bool check_moved(It first, It last, bool expected)
    {
        for ( ; first != last ; ++first )
            if ( first->moved() != expected )
                return false;
        return true;
    }

    template< class Container >
    void moved_test_impl( Container& c, bool expect_move)
    {
        using namespace boost::adaptors;

        {
            Container source = c;
            check_moved(source.begin(), source.end(), false);
            std::vector< copy_movable > test_result1;
            boost::push_back(test_result1, source | moved);
            check_moved(source.begin(), source.end(), expect_move);

            BOOST_CHECK_EQUAL_COLLECTIONS( c.begin(), c.end(),
                test_result1.begin(), test_result1.end() );
        }
        
        {
            Container source = c;
            check_moved(source.begin(), source.end(), false);
            std::vector< copy_movable > test_result2;
            boost::push_back(test_result2, adaptors::move(c));
            check_moved(source.begin(), source.end(), expect_move);

            BOOST_CHECK_EQUAL_COLLECTIONS( c.begin(), c.end(),
                test_result2.begin(), test_result2.end() );
        }
    }

    template< class Container >
    void moved_test_impl(bool expect_move)
    {
        using namespace boost::assign;

        Container c;

        // Test empty
        moved_test_impl(c, expect_move);

        // Test one
        c += copy_movable(1);
        moved_test_impl(c, expect_move);

        // Test many
        c += copy_movable(1),copy_movable(2),copy_movable(3);
        moved_test_impl(c, expect_move);
    }

    void moved_test()
    {
        moved_test_impl< std::vector< copy_movable > >(true);
        moved_test_impl< std::list< copy_movable > >(true);
        moved_test_impl< std::set< copy_movable > >(false);
        moved_test_impl< std::multiset< copy_movable > >(false);
    }
}


boost::unit_test::test_suite*
init_unit_test_suite(int argc, char* argv[])
{
    boost::unit_test::test_suite* test
        = BOOST_TEST_SUITE( "RangeTestSuite.adaptor.moved" );

    test->add( BOOST_TEST_CASE( &boost::moved_test ) );

    return test;
}
