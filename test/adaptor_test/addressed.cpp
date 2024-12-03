// Boost.Range library
//
//  Copyright Denis Mikhailov 2022.
//  Copyright Thorsten Ottosen, Neil Groves 2006 - 2008. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//

#include <boost/range/adaptor/addressed.hpp>

#include <boost/test/test_tools.hpp>
#include <boost/test/unit_test.hpp>

#include <boost/range.hpp>
#include <boost/assign.hpp>

#include <vector>

namespace boost
{
    namespace
    {
        void simple_test()
        {
            using namespace boost::assign;
            using namespace boost::adaptors;
            std::vector<int> a = list_of(1)(2)(3);
            BOOST_CHECK(boost::copy_range<std::vector<int*> >(a | addressed) 
                        == list_of(&a[0])(&a[1])(&a[2]));
            BOOST_CHECK(boost::copy_range<std::vector<int*> >(addressof(a)) 
                        == list_of(&a[0])(&a[1])(&a[2]));
        }

        void simple_const_test()
        {
            using namespace boost::assign;
            using namespace boost::adaptors;
            const std::vector<int> a = list_of(1)(2)(3);
            BOOST_CHECK(boost::copy_range<std::vector<const int*> >(a | addressed) 
                        == list_of(&a[0])(&a[1])(&a[2]));
            BOOST_CHECK(boost::copy_range<std::vector<const int*> >(addressof(a)) 
                        == list_of(&a[0])(&a[1])(&a[2]));
        }
    }
}

boost::unit_test::test_suite*
init_unit_test_suite(int argc, char* argv[])
{
    boost::unit_test::test_suite* test
        = BOOST_TEST_SUITE( "RangeTestSuite.adaptor.addressed" );

    test->add(BOOST_TEST_CASE(&boost::simple_test));
    test->add(BOOST_TEST_CASE(&boost::simple_const_test));

    return test;
}
