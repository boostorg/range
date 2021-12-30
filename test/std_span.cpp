    // Boost.Range library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//


#include <boost/detail/workaround.hpp>

#if BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x564))
#  pragma warn -8091 // suppress warning in Boost.Test
#  pragma warn -8057 // unused argument argc/argv in Boost.Test
#endif

#include <boost/range/functions.hpp>
#include <boost/range/metafunctions.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/test/test_tools.hpp>
#if __cpp_lib_span >= 201902L
#  include <span>
#endif

#if __cpp_lib_span >= 201902L
void check_std_span()
{
    // const_iterator was removed from std::span for C++20: https://cplusplus.github.io/LWG/issue3320
    // but see https://github.com/cplusplus/papers/issues/971 - it may be reintroduced as a std::const_iterator
    // Check that boost::begin etc. behave consistently with their respective member methods; this may require
    // additional work in future.

    std::array<int, 3> arr = {1, 2, 3};
    using span_t = std::span<int, 3>;
    span_t sp = arr;
    const span_t spc = sp;
    using cspan_t = std::span<const int, 3>;
    cspan_t csp = sp;
    const cspan_t cspc = csp;

    BOOST_STATIC_ASSERT(( boost::is_same< boost::range_value<span_t>::type, span_t::value_type >::value ));
    BOOST_STATIC_ASSERT(( boost::is_same< boost::range_iterator<span_t>::type, span_t::iterator >::value ));
    BOOST_STATIC_ASSERT(( boost::is_same< boost::range_difference<span_t>::type, span_t::difference_type >::value ));
    BOOST_STATIC_ASSERT(( boost::is_same< boost::range_size<span_t>::type, span_t::size_type >::value ));

    BOOST_CHECK( boost::begin( sp ) == sp.begin() );
    BOOST_CHECK( boost::end( sp )   == sp.end() );
    BOOST_CHECK( boost::empty( sp ) == sp.empty() );
    BOOST_CHECK( static_cast<std::size_t>(boost::size( sp )) == sp.size() );

    BOOST_STATIC_ASSERT(( boost::is_same< boost::range_value<const span_t>::type, span_t::value_type >::value ));
    BOOST_STATIC_ASSERT(( boost::is_same< boost::range_iterator<const span_t>::type, span_t::iterator >::value ));
    BOOST_STATIC_ASSERT(( boost::is_same< boost::range_difference<const span_t>::type, span_t::difference_type >::value ));
    BOOST_STATIC_ASSERT(( boost::is_same< boost::range_size<const span_t>::type, span_t::size_type >::value ));

    BOOST_CHECK( boost::begin( spc ) == spc.begin() );
    BOOST_CHECK( boost::end( spc )   == spc.end() );
    BOOST_CHECK( boost::empty( spc ) == spc.empty() );
    BOOST_CHECK( static_cast<std::size_t>(boost::size( spc )) == spc.size() );

    BOOST_STATIC_ASSERT(( boost::is_same< boost::range_value<cspan_t>::type, cspan_t::value_type >::value ));
    BOOST_STATIC_ASSERT(( boost::is_same< boost::range_iterator<cspan_t>::type, cspan_t::iterator >::value ));
    BOOST_STATIC_ASSERT(( boost::is_same< boost::range_difference<cspan_t>::type, cspan_t::difference_type >::value ));
    BOOST_STATIC_ASSERT(( boost::is_same< boost::range_size<cspan_t>::type, cspan_t::size_type >::value ));

    BOOST_CHECK( boost::begin( csp ) == csp.begin() );
    BOOST_CHECK( boost::end( csp )   == csp.end() );
    BOOST_CHECK( boost::empty( csp ) == csp.empty() );
    BOOST_CHECK( static_cast<std::size_t>(boost::size( csp )) == csp.size() );

    BOOST_STATIC_ASSERT(( boost::is_same< boost::range_value<const cspan_t>::type, cspan_t::value_type >::value ));
    BOOST_STATIC_ASSERT(( boost::is_same< boost::range_iterator<const cspan_t>::type, cspan_t::iterator >::value ));
    BOOST_STATIC_ASSERT(( boost::is_same< boost::range_difference<const cspan_t>::type, cspan_t::difference_type >::value ));
    BOOST_STATIC_ASSERT(( boost::is_same< boost::range_size<const cspan_t>::type, cspan_t::size_type >::value ));

    BOOST_CHECK( boost::begin( cspc ) == cspc.begin() );
    BOOST_CHECK( boost::end( cspc )   == cspc.end() );
    BOOST_CHECK( boost::empty( cspc ) == cspc.empty() );
    BOOST_CHECK( static_cast<std::size_t>(boost::size( cspc )) == cspc.size() );
}
#endif

#include <boost/test/unit_test.hpp>

boost::unit_test::test_suite* init_unit_test_suite( int argc, char* argv[] )
{
    boost::unit_test::test_suite* test = BOOST_TEST_SUITE( "Range Test Suite" );

#if __cpp_lib_span >= 201902L
    test->add( BOOST_TEST_CASE( &check_std_span ) );
#endif

    return test;
}
