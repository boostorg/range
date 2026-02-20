// Boost.Range library
//
//  Copyright Klaus Triendl 2020. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//
// For more information, see http://www.boost.org/libs/range/
//
#include <boost/range/algorithm/find.hpp>
#include <boost/range/adaptor/reversed.hpp>

#include <boost/test/test_tools.hpp>
#include <boost/test/unit_test.hpp>

#include <boost/assign.hpp>
#include "../test_driver/range_return_root_test_driver.hpp"
#include <algorithm>
#include <functional>
#include <list>
#include <numeric>
#include <deque>
#include <vector>

namespace boost_range_test_algorithm_find_return_root
{
    class find_return_root_test_policy
    {
    public:
        template<class View>
        BOOST_DEDUCED_TYPENAME boost::root_iterator_of<View>::type
        test_iter(View& rng)
        {
            typedef BOOST_DEDUCED_TYPENAME boost::root_iterator_of<View>::type iter_t;
            iter_t result = boost::find(rng, 3);
            iter_t result2 = boost::find(boost::make_iterator_range(rng), 3);
            BOOST_CHECK( result == result2 );
            return root_of(result);
        }

        template<boost::range_return_value return_type>
        struct test_range
        {
            template<class View, class Policy>
            BOOST_DEDUCED_TYPENAME boost::range_return<View,return_type>::type
            operator()(Policy&, View& rng)
            {
                typedef BOOST_DEDUCED_TYPENAME boost::range_return<View,return_type>::type result_t;
                result_t result = boost::find<return_type>(rng, 3);
                result_t result2 = boost::find<return_type>(boost::make_iterator_range(rng), 3);
                BOOST_CHECK( result == result2 );
                return result;
            }
        };

        template<class View>
        BOOST_DEDUCED_TYPENAME boost::root_iterator_of<View>::type
        reference(View& rng)
        {
            return root_of( std::find(boost::begin(rng), boost::end(rng), 3) );
        }
    };

    template<class Container>
    void test_find_container()
    {
        using namespace boost::assign;

        typedef BOOST_DEDUCED_TYPENAME boost::remove_const<Container>::type container_t;
        typedef boost::reversed_range<Container> view_t;

        boost::range_test::range_return_root_test_driver test_driver;

        container_t mcont;
        Container& cont = mcont;
        view_t v1(cont);
        test_driver(v1, find_test_policy());

        mcont.clear();
        mcont += 1;
        view_t v2(cont);
        test_driver(v2, find_test_policy());

        mcont.clear();
        mcont += 1,2,3,4,5,6,7,8,9;
        view_t v3(cont);
        test_driver(v3, find_test_policy());
    }

    void test_find()
    {
        test_find_container< std::vector<int> >();
        test_find_container< std::list<int> >();
        test_find_container< std::deque<int> >();

        test_find_container< const std::vector<int> >();
        test_find_container< const std::list<int> >();
        test_find_container< const std::deque<int> >();

        std::vector<int> vi(0);
        const std::vector<int>& cvi = vi;
        typedef std::vector<int>::const_iterator it_t;
        typedef boost::iterator_range<it_t> itrng_t;
        it_t it1_1 = root_of( boost::find(vi | boost::adaptors::reversed, 0) );
        it_t it2_1 = root_of( boost::find(cvi | boost::adaptors::reversed, 0) );
        BOOST_CHECK( it1_1 == it2_1 );
        it_t it1_2 = root_of( boost::find<boost::return_root_found>(vi | boost::adaptors::reversed, 0) );
        it_t it2_2 = root_of( boost::find<boost::return_root_found>(cvi | boost::adaptors::reversed, 0) );
        BOOST_CHECK( it1_2 == it2_2 );
        BOOST_CHECK( it1_1 == it1_2 );
        BOOST_CHECK( it2_1 == it2_2 );

        itrng_t itrng1_1 = root_of( boost::find<boost::return_found_end>(vi | boost::adaptors::reversed, 0) );
        itrng_t itrng2_1 = root_of( boost::find<boost::return_found_end>(cvi | boost::adaptors::reversed, 0) );
        BOOST_CHECK( itrng1_1 == itrng2_1 );
        itrng_t itrng1_2 = boost::find<boost::return_root_found_end>(vi | boost::adaptors::reversed, 0);
        itrng_t itrng2_2 = boost::find<boost::return_root_found_end>(cvi | boost::adaptors::reversed, 0);
        BOOST_CHECK( itrng1_2 == itrng2_2 );
        BOOST_CHECK( itrng1_1 == itrng1_2 );
        BOOST_CHECK( itrng2_1 == itrng2_2 );
    }
    
    // The find algorithm can be used like a "contains" algorithm
    // since the returned iterator_range is convertible to bool.
    // Therefore if the return value is an empty range it will
    // convert to the equivalent to "false" whereas a range that
    // is not empty will convert to "true". Therefore one can
    // use the syntax boost::find<boost::return_found_end>(rng, x)
    // as a contains function.
    void test_find_as_contains()
    {
        std::list<int> l;
        for (int i = 0; i < 10; ++i)
            l.push_back(i);
        
        BOOST_CHECK(boost::find<boost::return_root_found_end>(l | boost::adaptors::reversed, 3));
        BOOST_CHECK(!boost::find<boost::return_root_found_end>(l | boost::adaptors::reversed, 10));
    }
}

boost::unit_test::test_suite*
init_unit_test_suite(int argc, char* argv[])
{
    boost::unit_test::test_suite* test
        = BOOST_TEST_SUITE( "RangeTestSuite.algorithm.find.return_root" );

    test->add( BOOST_TEST_CASE( &boost_range_test_algorithm_find_return_root::test_find ) );
    test->add( BOOST_TEST_CASE( &boost_range_test_algorithm_find_return_root::test_find_as_contains ) );

    return test;
}
