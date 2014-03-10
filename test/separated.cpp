// Boost.Range library
//
//  Copyright Neil Groves 2014. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//
#include <boost/range/separated.hpp>
#include <boost/cstdint.hpp>
#include <boost/test/test_tools.hpp>
#include <boost/test/unit_test.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

namespace boost_range_test
{
    namespace
    {

void test_separated1()
{
    std::vector<boost::int32_t> v;
    for (boost::int32_t i = 0; i < 10; ++i)
        v.push_back(i);

    std::ostringstream out;
    out << '{' << boost::range::separated(v, ',') << '}';

    BOOST_CHECK_EQUAL(out.str(), "{0,1,2,3,4,5,6,7,8,9}");
}

void test_separated2()
{
    std::vector<boost::int32_t> v;
    v.push_back(3);

    std::ostringstream out;
    out << '{' << boost::range::separated(v, ',') << '}';

    BOOST_CHECK_EQUAL(out.str(), "{3}");
}

void test_separated3()
{
    std::vector<boost::int32_t> v;

    std::ostringstream out;
    out << '{' << boost::range::separated(v, ',') << '}';

    BOOST_CHECK_EQUAL(out.str(), "{}");
}

void test_separated4()
{
    std::vector<boost::int32_t> v;
    for (boost::int32_t i = 0; i < 5; ++i)
        v.push_back(i);

    std::ostringstream out;
    out << '{' << boost::range::separated(v, "::") << '}';

    BOOST_CHECK_EQUAL(out.str(), "{0::1::2::3::4}");
}

struct udt_separator
{
};

template<typename Char, typename Traits>
inline std::basic_ostream<Char,Traits>&
operator<<(std::basic_ostream<Char,Traits>& out, udt_separator)
{
    return out << "[sep]";
}

void test_separated5()
{
    std::vector<boost::int32_t> v;
    for (boost::int32_t i = 0; i < 5; ++i)
        v.push_back(i);

    std::ostringstream out;
    out << '{' << boost::range::separated(v, udt_separator()) << '}';

    BOOST_CHECK_EQUAL(out.str(), "{0[sep]1[sep]2[sep]3[sep]4}");
}

    } // anonymous namespace
} // namespace boost_range_test

boost::unit_test::test_suite* init_unit_test_suite(int, char*[] )
{
    boost::unit_test::test_suite* test =
            BOOST_TEST_SUITE( "Boost.Range separated test suite" );

    test->add(BOOST_TEST_CASE(&boost_range_test::test_separated1));
    test->add(BOOST_TEST_CASE(&boost_range_test::test_separated2));
    test->add(BOOST_TEST_CASE(&boost_range_test::test_separated3));
    test->add(BOOST_TEST_CASE(&boost_range_test::test_separated4));
    test->add(BOOST_TEST_CASE(&boost_range_test::test_separated5));

    return test;
}
