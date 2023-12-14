// Boost.Range library
//
//  Copyright Neil Groves 2009.
//  Copyright Adam Wulkiewicz 2014.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//
#include <boost/range/algorithm/move_backward.hpp>

#include <boost/test/test_tools.hpp>
#include <boost/test/unit_test.hpp>

#include <boost/assign.hpp>
#include <boost/range/iterator.hpp>
#include <algorithm>
#include <list>
#include <set>
#include <vector>

#include "../copymovable.hpp"

namespace boost
{
    namespace
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
        void test_move_backward_impl(bool expect_move)
        {
            typedef BOOST_DEDUCED_TYPENAME Container::value_type value_t;

            std::vector<value_t> input;
            input.push_back(copy_movable(1));
            input.push_back(copy_movable(2));
            input.push_back(copy_movable(3));

            {
                Container source(input.begin(), input.end());

                BOOST_CHECK(check_moved(source.begin(), source.end(), false));

                std::vector<value_t> target;
                target.resize(source.size());

                typedef BOOST_DEDUCED_TYPENAME range_iterator< std::vector<value_t> >::type iterator_t;

                iterator_t it = boost::move_backward(source, target.end());

                BOOST_CHECK(check_moved(source.begin(), source.end(), expect_move));

                BOOST_CHECK( it == target.begin() );

                BOOST_CHECK_EQUAL_COLLECTIONS(
                    target.begin(), target.end(),
                    input.begin(), input.end()
                    );
            }

            {
                Container source(input.begin(), input.end());

                BOOST_CHECK(check_moved(source.begin(), source.end(), false));

                std::vector<value_t> target;
                target.resize(source.size());

                typedef BOOST_DEDUCED_TYPENAME range_iterator< std::vector<value_t> >::type iterator_t;

                iterator_t it = boost::move_backward(boost::make_iterator_range(source), target.end());

                BOOST_CHECK(check_moved(source.begin(), source.end(), expect_move));

                BOOST_CHECK( it == target.begin() );

                BOOST_CHECK_EQUAL_COLLECTIONS(
                    target.begin(), target.end(),
                    input.begin(), input.end()
                    );
            }
        }

        void test_move_backward()
        {
            test_move_backward_impl< std::vector<copy_movable> >(true);
            test_move_backward_impl< std::list<copy_movable> >(true);
            test_move_backward_impl< std::set<copy_movable> >(false);
            test_move_backward_impl< std::multiset<copy_movable> >(false);
        }
    }
}


boost::unit_test::test_suite*
init_unit_test_suite(int argc, char* argv[])
{
    boost::unit_test::test_suite* test
        = BOOST_TEST_SUITE( "RangeTestSuite.algorithm.move_backward" );

    test->add( BOOST_TEST_CASE( &boost::test_move_backward ) );

    return test;
}
