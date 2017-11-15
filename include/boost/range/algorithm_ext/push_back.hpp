// Boost.Range library
//
//  Copyright Neil Groves 2009. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//
#ifndef BOOST_RANGE_ALGORITHM_EXT_PUSH_BACK_HPP_INCLUDED
#define BOOST_RANGE_ALGORITHM_EXT_PUSH_BACK_HPP_INCLUDED

#include <boost/range/config.hpp>
#include <boost/range/concepts.hpp>
#include <boost/range/difference_type.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/detail/implementation_help.hpp>
#include <boost/assert.hpp>

namespace boost
{
#if !defined( BOOST_NO_CXX11_RVALUE_REFERENCES )
    namespace range_detail
    {

template < class Container, class Range >
inline Container& push_back_impl( Container& on, Range&& from, std::false_type)
{
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<Range> ));
    BOOST_ASSERT_MSG(!range_detail::is_same_object(on, from),
        "cannot move from a container to itself");
    on.insert( on.end(),
               std::make_move_iterator(boost::begin(from)),
               std::make_move_iterator(boost::end(from)));
    return on;
}

template < class Container, class Range >
inline Container& push_back_impl( Container& on, const Range& from, std::true_type)
{
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const Range> ));
    BOOST_ASSERT_MSG(!range_detail::is_same_object(on, from),
        "cannot copy from a container to itself");
    on.insert( on.end(), boost::begin(from), boost::end(from));
    return on;
}

    } //namespace range_detail
#endif

    namespace range {
#if defined( BOOST_NO_CXX11_RVALUE_REFERENCES )
template< class Container, class Range >
inline Container& push_back( Container& on, const Range& from )
{
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<Container> ));
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const Range> ));
    BOOST_ASSERT_MSG(!range_detail::is_same_object(on, from),
        "cannot copy from a container to itself");
    on.insert( on.end(), boost::begin(from), boost::end(from) );
    return on;
}

#else

template< class Container, class Range >
inline Container& push_back( Container& on, Range&& from )
{
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<Container> ));
    range_detail::push_back_impl(on,
                                 std::forward<Range>(from),
                                 std::is_lvalue_reference<Range>() );
    return on;
}

#endif
    } // namespace range
    using range::push_back;
} // namespace boost

#endif // include guard
