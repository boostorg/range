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
    void moved_test_impl( Container& c)
    {
        using namespace boost::adaptors;

        {
            Container source(c.begin(), c.end());
            check_moved(source.begin(), source.end(), false);
            std::vector< copy_movable > test_result1;
            boost::push_back(test_result1, source | moved);
            check_moved(source.begin(), source.end(), true);

            BOOST_CHECK_EQUAL_COLLECTIONS( c.begin(), c.end(),
                test_result1.begin(), test_result1.end() );
        }
        
        {
            Container source(c.begin(), c.end());
            check_moved(source.begin(), source.end(), false);
            std::vector< copy_movable > test_result2;
            boost::push_back(test_result2, adaptors::move(source));
            check_moved(source.begin(), source.end(), true);

            BOOST_CHECK_EQUAL_COLLECTIONS( c.begin(), c.end(),
                test_result2.begin(), test_result2.end() );
        }
    }

    template< class Container >
    void moved_test_impl()
    {
        using namespace boost::assign;

        Container c;

        // Test empty
        moved_test_impl(c);

        // Test one
        copy_movable c1(1);
        c += c1;
        moved_test_impl(c);

        // Test many
        copy_movable c2(2);
        copy_movable c3(3);
        c += c2, c3;
        moved_test_impl(c);
    }

    void moved_test()
    {
        moved_test_impl< std::vector< copy_movable > >();
        moved_test_impl< std::list< copy_movable > >();
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
