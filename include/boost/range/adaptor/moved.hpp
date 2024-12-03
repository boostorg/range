// Boost.Range library
//
// Copyright Thorsten Ottosen, Neil Groves 2006 - 2008.
// Copyright Adam Wulkiewicz 2014.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_RANGE_ADAPTOR_MOVED_HPP
#define BOOST_RANGE_ADAPTOR_MOVED_HPP

#include <boost/range/adaptor/argument_fwd.hpp>
#include <boost/range/iterator_range.hpp>

#include <boost/move/iterator.hpp>

namespace boost {

namespace range_detail {

template< class R >
struct moved_range :
    boost::iterator_range<
        boost::move_iterator<
            BOOST_DEDUCED_TYPENAME range_iterator<R>::type
        >
    >
{
private:
    typedef boost::iterator_range<
                boost::move_iterator<
                    BOOST_DEDUCED_TYPENAME range_iterator<R>::type
                >
            > base;
public:
    moved_range( R & r )
        : base( boost::make_move_iterator(boost::begin(r)),
                boost::make_move_iterator(boost::end(r)) )
    { }
};

struct move_forwarder {};

template< class InputRange >
inline moved_range<InputRange>
operator|( InputRange & r, move_forwarder )
{
    return moved_range<InputRange>( r );
}

template< class InputRange >
inline moved_range<InputRange const>
operator|( InputRange const& r, move_forwarder )
{
    return moved_range<InputRange const>( r );
}

} // namespace range_detail

// Unusual use of 'using' is intended to bring filter_range into the boost namespace
// while leaving the mechanics of the '|' operator in range_detail and maintain
// argument dependent lookup.
// filter_range logically needs to be in the boost namespace to allow user of
// the library to define the return type for filter()
using range_detail::moved_range;

namespace adaptors {

namespace
{
    const range_detail::move_forwarder moved =
                                    range_detail::move_forwarder();
}

template<class InputRange>
inline moved_range<InputRange>
move(InputRange & rng)
{
    return moved_range<InputRange>(rng);
}

template<class InputRange>
inline moved_range<InputRange const>
move(InputRange const& rng)
{
    return moved_range<InputRange const>(rng);
}

} // namespace adaptors

} // namespace boost

#endif // BOOST_RANGE_ADAPTOR_MOVED_HPP
