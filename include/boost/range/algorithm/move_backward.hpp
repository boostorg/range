// Boost.Range library
//
//  Copyright Neil Groves 2009.
//  Copyright Adam Wulkiewicz 2014.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_RANGE_ALGORITHM_MOVE_BACKWARD_HPP
#define BOOST_RANGE_ALGORITHM_MOVE_BACKWARD_HPP

#include <boost/concept_check.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/concepts.hpp>

#include <boost/move/algorithm.hpp>

namespace boost {

namespace range {

/// \brief template function copy_backward
///
/// range-based version of the move_backwards std algorithm
///
/// \pre BidirectionalRange is a model of the BidirectionalRangeConcept
/// \pre BidirectionalTraversalWriteableIterator is a model of the BidirectionalIteratorConcept
/// \pre BidirectionalTraversalWriteableIterator is a model of the WriteableIteratorConcept
template< class BidirectionalRange, class BidirectionalTraversalWriteableIterator >
inline BidirectionalTraversalWriteableIterator
move_backward(BidirectionalRange & rng,
              BidirectionalTraversalWriteableIterator out)
{
    BOOST_RANGE_CONCEPT_ASSERT(( BidirectionalRangeConcept<BidirectionalRange> ));
    return ::boost::move_backward(::boost::begin(rng), ::boost::end(rng), out);
}

/// \brief template function copy_backward
///
/// range-based version of the move_backwards std algorithm
///
/// \pre BidirectionalRange is a model of the BidirectionalRangeConcept
/// \pre BidirectionalTraversalWriteableIterator is a model of the BidirectionalIteratorConcept
/// \pre BidirectionalTraversalWriteableIterator is a model of the WriteableIteratorConcept
template< class BidirectionalRange, class BidirectionalTraversalWriteableIterator >
inline BidirectionalTraversalWriteableIterator
move_backward(BidirectionalRange const& rng,
              BidirectionalTraversalWriteableIterator out)
{
    BOOST_RANGE_CONCEPT_ASSERT(( BidirectionalRangeConcept<BidirectionalRange const> ));
    return ::boost::move_backward(::boost::begin(rng), ::boost::end(rng), out);
}

} // namespace range

using range::move_backward;

} // namespace boost

#endif // BOOST_RANGE_ALGORITHM_MOVE_BACKWARD_HPP
