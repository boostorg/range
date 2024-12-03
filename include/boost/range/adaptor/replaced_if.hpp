// Boost.Range library
//
//  Copyright Neil Groves 2007. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//

#ifndef BOOST_RANGE_ADAPTOR_REPLACED_IF_IMPL_HPP_INCLUDED
#define BOOST_RANGE_ADAPTOR_REPLACED_IF_IMPL_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/range/adaptor/argument_fwd.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/reference.hpp>
#include <boost/range/concepts.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/transform_iterator.hpp>
#include <boost/optional/optional.hpp>
#include <boost/move/utility_core.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/is_reference.hpp>
#include <boost/type_traits/conditional.hpp>

namespace boost
{
    namespace range_detail
    {
        template< class Pred, class Reference >
        class replace_value_if
        {
        public:
            typedef BOOST_DEDUCED_TYPENAME boost::conditional<boost::is_reference<Reference>::value,
                                                              const BOOST_DEDUCED_TYPENAME boost::remove_reference<Reference>::type&,
                                                              Reference>::type result_type;
            typedef Reference first_argument_type;

            // Rationale:
            // required to allow the iterator to be default constructible.
            replace_value_if()
            {
            }

            replace_value_if(const Pred& pred, const BOOST_DEDUCED_TYPENAME boost::remove_reference<Reference>::type& to)
                : m_impl(data(pred, to))
            {
            }

            result_type operator()(Reference x) const
            {
            #if defined(BOOST_NO_CXX11_RVALUE_REFERENCES) 
                return m_impl->m_pred(x) ? m_impl->m_to : x;
            #else
                return m_impl->m_pred(x) ? m_impl->m_to : boost::forward<Reference>(x);
            #endif
            }

        private:
            

            struct data
            {
                data(const Pred& p, const BOOST_DEDUCED_TYPENAME boost::remove_reference<Reference>::type& t)
                    : m_pred(p), m_to(t)
                {
                }

                Pred  m_pred;
                BOOST_DEDUCED_TYPENAME boost::remove_const<BOOST_DEDUCED_TYPENAME boost::remove_reference<Reference>::type>::type m_to;
            };
            boost::optional<data> m_impl;
        };

        template< class Pred, class R >
        class replaced_if_range :
            public boost::iterator_range<
                boost::transform_iterator<
                    replace_value_if< Pred, BOOST_DEDUCED_TYPENAME range_reference<R>::type >,
                    BOOST_DEDUCED_TYPENAME range_iterator<R>::type > >
        {
        private:
            typedef replace_value_if< Pred, BOOST_DEDUCED_TYPENAME range_reference<R>::type > Fn;

            typedef boost::iterator_range<
                boost::transform_iterator<
                    replace_value_if< Pred, BOOST_DEDUCED_TYPENAME range_reference<R>::type >,
                    BOOST_DEDUCED_TYPENAME range_iterator<R>::type > > base_t;

        public:
            typedef BOOST_DEDUCED_TYPENAME range_reference<R>::type reference_type;

            replaced_if_range( R& r, const Pred& pred, const BOOST_DEDUCED_TYPENAME boost::remove_reference<reference_type>::type& to )
                : base_t( make_transform_iterator( boost::begin(r), Fn(pred, to) ),
                          make_transform_iterator( boost::end(r), Fn(pred, to) ) )
            { }
        };

        template< class Pred, class T >
        class replace_if_holder
        {
        public:
            replace_if_holder( const Pred& pred, const T& to )
                : m_pred(pred), m_to(to)
            { }

            const Pred& pred() const { return m_pred; }
            const T& to() const { return m_to; }

        private:
            Pred m_pred;
            T m_to;
        };

        template< class Pred, class SinglePassRange, class Value >
        inline replaced_if_range<Pred, SinglePassRange>
        operator|(SinglePassRange& r, const replace_if_holder<Pred, Value>& f)
        {
            BOOST_RANGE_CONCEPT_ASSERT((
                SinglePassRangeConcept<SinglePassRange>));

            return replaced_if_range<Pred, SinglePassRange>(
                r, f.pred(), f.to());
        }

        template< class Pred, class SinglePassRange, class Value >
        inline replaced_if_range<Pred, const SinglePassRange>
        operator|(const SinglePassRange& r, const replace_if_holder<Pred, Value>& f)
        {
            BOOST_RANGE_CONCEPT_ASSERT((
                SinglePassRangeConcept<const SinglePassRange>));

            return replaced_if_range<Pred, const SinglePassRange>(
                r, f.pred(), f.to());
        }
    } // 'range_detail'

    using range_detail::replaced_if_range;

    namespace adaptors
    {
        namespace
        {
            const range_detail::forwarder2TU<range_detail::replace_if_holder>
                replaced_if =
                    range_detail::forwarder2TU<range_detail::replace_if_holder>();
        }

        template< class Pred, class SinglePassRange, class Value >
        inline replaced_if_range<Pred, SinglePassRange>
        replace_if(SinglePassRange& rng, Pred pred, Value to)
        {
            BOOST_RANGE_CONCEPT_ASSERT((
                SinglePassRangeConcept<SinglePassRange>));

            return range_detail::replaced_if_range<Pred, SinglePassRange>(
                rng, pred, to);
        }

        template< class Pred, class SinglePassRange, class Value >
        inline replaced_if_range<Pred, const SinglePassRange>
        replace_if(const SinglePassRange& rng, Pred pred, Value to)
        {
            BOOST_RANGE_CONCEPT_ASSERT((
                SinglePassRangeConcept<const SinglePassRange>));

            return range_detail::replaced_if_range<Pred, const SinglePassRange>(
                rng, pred, to);
        }
    } // 'adaptors'

} // 'boost'

#endif // include guard
