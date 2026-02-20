//  Copyright Neil Groves 2009. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//
// For more information, see http://www.boost.org/libs/range/
//
#ifndef BOOST_RANGE_DETAIL_RANGE_RETURN_HPP_INCLUDED
#define BOOST_RANGE_DETAIL_RANGE_RETURN_HPP_INCLUDED

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/root_iterator_of.hpp>
#include <boost/next_prior.hpp>

namespace boost
{
    enum range_return_value
    {
        // (*) indicates the most common values
        return_found,            // only the found resulting iterator (*)
        return_next,             // next(found) iterator
        return_prior,            // prior(found) iterator
        return_begin_found,      // [begin, found) range (*)
        return_begin_next,       // [begin, next(found)) range
        return_begin_prior,      // [begin, prior(found)) range
        return_found_end,        // [found, end) range (*)
        return_next_end,         // [next(found), end) range
        return_prior_end,        // [prior(found), end) range
        return_begin_end,        // [begin, end) range
        return_root_found,       // only the found resulting root iterator (*)
        return_root_next,        // next(found) root iterator
        return_root_prior,       // prior(found) root iterator
        return_root_begin_found, // [begin, found) root iterator range (*)
        return_root_begin_next,  // [begin, next(found)) root iterator range
        return_root_begin_prior, // [begin, prior(found)) root iterator range
        return_root_found_end,   // [found, end) root iterator range (*)
        return_root_next_end,    // [next(found), end) root iterator range
        return_root_prior_end,   // [prior(found), end) root iterator range
        return_root_begin_end,   // [begin, end) root iterator range
    };

    template< class SinglePassRange, range_return_value >
    struct range_return
    {
        typedef boost::iterator_range<
            BOOST_DEDUCED_TYPENAME range_iterator<SinglePassRange>::type > type;

        static type pack(BOOST_DEDUCED_TYPENAME range_iterator<SinglePassRange>::type found,
                         SinglePassRange& rng)
        {
            return type(found, boost::end(rng));
        }
    };

    template< class SinglePassRange >
    struct range_return< SinglePassRange, return_found >
    {
        typedef BOOST_DEDUCED_TYPENAME range_iterator<SinglePassRange>::type type;

        static type pack(type found, SinglePassRange&)
        {
            return found;
        }
    };

    template< class SinglePassRange >
    struct range_return< SinglePassRange, return_next >
    {
        typedef BOOST_DEDUCED_TYPENAME range_iterator<SinglePassRange>::type type;

        static type pack(type found, SinglePassRange& rng)
        {
            return found == boost::end(rng)
                ? found
                : boost::next(found);
        }
    };

    template< class BidirectionalRange >
    struct range_return< BidirectionalRange, return_prior >
    {
        typedef BOOST_DEDUCED_TYPENAME range_iterator<BidirectionalRange>::type type;

        static type pack(type found, BidirectionalRange& rng)
        {
            return found == boost::begin(rng)
                ? found
                : boost::prior(found);
        }
    };

    template< class SinglePassRange >
    struct range_return< SinglePassRange, return_begin_found >
    {
        typedef boost::iterator_range<
            BOOST_DEDUCED_TYPENAME range_iterator<SinglePassRange>::type > type;

        static type pack(BOOST_DEDUCED_TYPENAME range_iterator<SinglePassRange>::type found,
                         SinglePassRange& rng)
        {
            return type(boost::begin(rng), found);
        }
    };

    template< class SinglePassRange >
    struct range_return< SinglePassRange, return_begin_next >
    {
        typedef boost::iterator_range<
            BOOST_DEDUCED_TYPENAME range_iterator<SinglePassRange>::type > type;

        static type pack(BOOST_DEDUCED_TYPENAME range_iterator<SinglePassRange>::type found,
                         SinglePassRange& rng)
        {
            return type( boost::begin(rng), 
                         found == boost::end(rng) ? found : boost::next(found) );
        }
    };

    template< class BidirectionalRange >
    struct range_return< BidirectionalRange, return_begin_prior >
    {
        typedef boost::iterator_range<
            BOOST_DEDUCED_TYPENAME range_iterator<BidirectionalRange>::type > type;

        static type pack(BOOST_DEDUCED_TYPENAME range_iterator<BidirectionalRange>::type found,
                         BidirectionalRange& rng)
        {
            return type( boost::begin(rng),
                         found == boost::begin(rng) ? found : boost::prior(found) );
        }
    };

    template< class SinglePassRange >
    struct range_return< SinglePassRange, return_found_end >
    {
        typedef boost::iterator_range<
            BOOST_DEDUCED_TYPENAME range_iterator<SinglePassRange>::type > type;

        static type pack(BOOST_DEDUCED_TYPENAME range_iterator<SinglePassRange>::type found,
                         SinglePassRange& rng)
        {
            return type(found, boost::end(rng));
        }
    };

    template< class SinglePassRange >
    struct range_return< SinglePassRange, return_next_end >
    {
        typedef boost::iterator_range<
            BOOST_DEDUCED_TYPENAME range_iterator<SinglePassRange>::type > type;

        static type pack(BOOST_DEDUCED_TYPENAME range_iterator<SinglePassRange>::type found,
                         SinglePassRange& rng)
        {
            return type( found == boost::end(rng) ? found : boost::next(found),
                         boost::end(rng) );
        }
    };

    template< class BidirectionalRange >
    struct range_return< BidirectionalRange, return_prior_end >
    {
        typedef boost::iterator_range<
            BOOST_DEDUCED_TYPENAME range_iterator<BidirectionalRange>::type > type;

        static type pack(BOOST_DEDUCED_TYPENAME range_iterator<BidirectionalRange>::type found,
                         BidirectionalRange& rng)
        {
            return type( found == boost::begin(rng) ? found : boost::prior(found),
                         boost::end(rng) );
        }
    };

    template< class SinglePassRange >
    struct range_return< SinglePassRange, return_begin_end >
    {
        typedef boost::iterator_range<
            BOOST_DEDUCED_TYPENAME range_iterator<SinglePassRange>::type > type;

        static type pack(BOOST_DEDUCED_TYPENAME range_iterator<SinglePassRange>::type,
                         SinglePassRange& rng)
        {
            return type(boost::begin(rng), boost::end(rng));
        }
    };

    template< class SinglePassRange >
    struct range_return< SinglePassRange, return_root_found >
    {
        typedef BOOST_DEDUCED_TYPENAME range_iterator<SinglePassRange>::type iterator;
        typedef BOOST_DEDUCED_TYPENAME root_iterator_of<iterator>::type root_iterator;
        // range return type
        typedef root_iterator type;

        static type pack(iterator found, SinglePassRange&)
        {
            return root_of(found);
        }
    };

    template< class SinglePassRange >
    struct range_return< SinglePassRange, return_root_next >
    {
        typedef BOOST_DEDUCED_TYPENAME range_iterator<SinglePassRange>::type iterator;
        typedef BOOST_DEDUCED_TYPENAME root_iterator_of<iterator>::type root_iterator;
        // range return type
        typedef root_iterator type;

        static type pack(iterator found, SinglePassRange& rng)
        {
            return found == boost::end(rng)
                ? root_of(found)
                : root_of(boost::next(found));
        }
    };

    template< class BidirectionalRange >
    struct range_return< BidirectionalRange, return_root_prior >
    {
        typedef BOOST_DEDUCED_TYPENAME range_iterator<BidirectionalRange>::type iterator;
        typedef BOOST_DEDUCED_TYPENAME root_iterator_of<iterator>::type root_iterator;
        // range return type
        typedef root_iterator type;

        static type pack(iterator found, BidirectionalRange& rng)
        {
            return found == boost::begin(rng)
                ? root_of(found)
                : root_of(boost::prior(found));
        }
    };

    template< class SinglePassRange >
    struct range_return< SinglePassRange, return_root_begin_found >
    {
        typedef BOOST_DEDUCED_TYPENAME range_iterator<SinglePassRange>::type iterator;
        typedef BOOST_DEDUCED_TYPENAME root_iterator_of<iterator>::type root_iterator;
        // range return type
        typedef iterator_range<root_iterator> type;

        static type pack(iterator found, SinglePassRange& rng)
        {
            return type( root_of(boost::begin(rng)),
                         root_of(found) );
        }
    };

    template< class SinglePassRange >
    struct range_return< SinglePassRange, return_root_begin_next >
    {
        typedef BOOST_DEDUCED_TYPENAME range_iterator<SinglePassRange>::type iterator;
        typedef BOOST_DEDUCED_TYPENAME root_iterator_of<iterator>::type root_iterator;
        // range return type
        typedef iterator_range<root_iterator> type;

        static type pack(iterator found, SinglePassRange& rng)
        {
            return type( root_of(boost::begin(rng)), 
                         found == boost::end(rng)
                         ? root_of(found)
                         : root_of(boost::next(found)) );
        }
    };

    template< class BidirectionalRange >
    struct range_return< BidirectionalRange, return_root_begin_prior >
    {
        typedef BOOST_DEDUCED_TYPENAME range_iterator<BidirectionalRange>::type iterator;
        typedef BOOST_DEDUCED_TYPENAME root_iterator_of<iterator>::type root_iterator;
        // range return type
        typedef iterator_range<root_iterator> type;

        static type pack(iterator found, BidirectionalRange& rng)
        {
            return type( root_of(boost::begin(rng)),
                         found == boost::begin(rng)
                         ? root_of(found)
                         : root_of(boost::prior(found)) );
        }
    };

    template< class SinglePassRange >
    struct range_return< SinglePassRange, return_root_found_end >
    {
        typedef BOOST_DEDUCED_TYPENAME range_iterator<SinglePassRange>::type iterator;
        typedef BOOST_DEDUCED_TYPENAME root_iterator_of<iterator>::type root_iterator;
        // range return type
        typedef iterator_range<root_iterator> type;

        static type pack(iterator found, SinglePassRange& rng)
        {
            return type( root_of(found),
                         root_of(boost::end(rng)) );
        }
    };

    template< class SinglePassRange >
    struct range_return< SinglePassRange, return_root_next_end >
    {
        typedef BOOST_DEDUCED_TYPENAME range_iterator<SinglePassRange>::type iterator;
        typedef BOOST_DEDUCED_TYPENAME root_iterator_of<iterator>::type root_iterator;
        // range return type
        typedef iterator_range<root_iterator> type;

        static type pack(iterator found, SinglePassRange& rng)
        {
            return type( found == boost::end(rng)
                         ? root_of(found)
                         : root_of(boost::next(found)),
                         root_of(boost::end(rng)) );
        }
    };

    template< class BidirectionalRange >
    struct range_return< BidirectionalRange, return_root_prior_end >
    {
        typedef BOOST_DEDUCED_TYPENAME range_iterator<BidirectionalRange>::type iterator;
        typedef BOOST_DEDUCED_TYPENAME root_iterator_of<iterator>::type root_iterator;
        // range return type
        typedef iterator_range<root_iterator> type;

        static type pack(iterator found, BidirectionalRange& rng)
        {
            return type( found == boost::begin(rng)
                         ? root_of(found)
                         : root_of(boost::prior(found)),
                         root_of(boost::end(rng)) );
        }
    };

    template< class SinglePassRange >
    struct range_return< SinglePassRange, return_root_begin_end >
    {
        typedef BOOST_DEDUCED_TYPENAME range_iterator<SinglePassRange>::type iterator;
        typedef BOOST_DEDUCED_TYPENAME root_iterator_of<iterator>::type root_iterator;
        // range return type
        typedef iterator_range<root_iterator> type;

        static type pack(iterator, SinglePassRange& rng)
        {
            return type( root_of(boost::begin(rng)),
                         root_of(boost::end(rng)) );
        }
    };

}

#endif // include guard
