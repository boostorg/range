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

#ifndef BOOST_RANGE_ADAPTOR_ADDRESSED_HPP
#define BOOST_RANGE_ADAPTOR_ADDRESSED_HPP

#include <boost/range/adaptor/transformed.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/is_reference.hpp>
#include <boost/static_assert.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/reference.hpp>
#include <boost/range/concepts.hpp>
#include <boost/range/reference.hpp>
#include <boost/range/iterator.hpp>

#include <boost/core/addressof.hpp>

#include <utility>

namespace boost
{
    namespace range_detail
    {
        struct addressof_forwarder {};

        template<typename Reference>
        struct addressof_value
        {
            BOOST_STATIC_ASSERT(boost::is_reference<Reference>::value);
            typedef typename boost::remove_reference<Reference>::type* result_type;
            typedef Reference argument_type;

            result_type operator()(argument_type x) const
            {
                return boost::addressof(x);
            }
        };

        template< typename R >
        struct addressof_range :
            boost::iterator_range<
                boost::transform_iterator<
                    addressof_value<typename boost::range_reference<R>::type>,
                    typename boost::range_iterator<R>::type> >
        {
        private:
            typedef typename boost::range_reference<R>::type reference_type;
            typedef typename boost::range_iterator<R>::type iterator_base;
            typedef addressof_value<reference_type> Fn;
            typedef boost::transform_iterator<Fn, iterator_base> iterator;
            typedef boost::iterator_range<iterator> base;

        public:
            addressof_range(R& r)
                : base(iterator(boost::begin(r), Fn()),
                    iterator(boost::end(r), Fn()))
            { }
        };

        template< class SinglePassRange >
        inline addressof_range<SinglePassRange>
        operator|( SinglePassRange& r, addressof_forwarder )
        {
            BOOST_RANGE_CONCEPT_ASSERT((
                SinglePassRangeConcept<SinglePassRange>));

            return addressof_range<SinglePassRange>( r );
        }

        template< class SinglePassRange >
        inline addressof_range<const SinglePassRange>
        operator|( const SinglePassRange& r, addressof_forwarder )
        {
            BOOST_RANGE_CONCEPT_ASSERT((
                SinglePassRangeConcept<SinglePassRange>));

            return addressof_range<const SinglePassRange>( r );
        }

    }

    using range_detail::addressof_range;

    namespace adaptors
    {
        namespace
        {
            const range_detail::addressof_forwarder addressed = 
                                    range_detail::addressof_forwarder();
        }

        template<class SinglePassRange>
        inline addressof_range<SinglePassRange>
        addressof(SinglePassRange& rng)
        {
            BOOST_RANGE_CONCEPT_ASSERT((
                SinglePassRangeConcept<SinglePassRange>));

            return addressof_range<SinglePassRange>( rng );
        }

        template<class SinglePassRange>
        inline addressof_range<const SinglePassRange>
        addressof(const SinglePassRange& rng)
        {
            BOOST_RANGE_CONCEPT_ASSERT((
                SinglePassRangeConcept<SinglePassRange>));

            return addressof_range<const SinglePassRange>( rng );
        }
    } // 'adaptors'

}

#endif
