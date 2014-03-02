// Boost.Range library
//
//  Copyright Neil Groves 2009.
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//

#ifndef BOOST_RANGE_SUB_RANGE_HPP
#define BOOST_RANGE_SUB_RANGE_HPP

#include <boost/detail/workaround.hpp>

#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1500)) 
    #pragma warning( push )
    #pragma warning( disable : 4996 )
#endif

#include <boost/range/config.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/value_type.hpp>
#include <boost/range/size_type.hpp>
#include <boost/range/difference_type.hpp>
#include <boost/range/algorithm/equal.hpp>
#include <boost/assert.hpp>
#include <boost/type_traits/is_reference.hpp>
#include <boost/type_traits/remove_reference.hpp>

namespace boost
{

    template< class ForwardRange > 
    class sub_range
        : public iterator_range<
            BOOST_DEDUCED_TYPENAME range_iterator<ForwardRange>::type
        > 
    {
        typedef BOOST_DEDUCED_TYPENAME range_iterator<ForwardRange>::type iterator_t;
        typedef iterator_range< iterator_t  > base;

        typedef BOOST_DEDUCED_TYPENAME base::impl impl;

    public:
        typedef BOOST_DEDUCED_TYPENAME range_value<ForwardRange>::type            value_type;
        typedef BOOST_DEDUCED_TYPENAME range_iterator<ForwardRange>::type         iterator;
        typedef BOOST_DEDUCED_TYPENAME range_iterator<const ForwardRange>::type   const_iterator;
        typedef BOOST_DEDUCED_TYPENAME range_difference<ForwardRange>::type       difference_type;
        typedef BOOST_DEDUCED_TYPENAME range_size<ForwardRange>::type             size_type;
        typedef BOOST_DEDUCED_TYPENAME base::reference                            reference;

    private:
        template<class Source>
        struct is_compatible_range
            : is_convertible<
                BOOST_DEDUCED_TYPENAME mpl::eval_if<
                    has_range_iterator<Source>,
                    range_iterator<Source>,
                    mpl::identity<void>
                >::type,
                iterator
            >
        {
        };

    public:
        sub_range()
        { }

#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1500) ) 
        sub_range( const sub_range& r ) 
            : base( static_cast<const base&>( r ) )  
        { }  
#endif

        template< class ForwardRange2 >
        sub_range(
            ForwardRange2& r,
            BOOST_DEDUCED_TYPENAME enable_if<
                is_compatible_range<ForwardRange2>
            >::type* = 0
        ) : 

#if BOOST_WORKAROUND(BOOST_INTEL_CXX_VERSION, <= 800 )
            base( impl::adl_begin( r ), impl::adl_end( r ) )
#else
            base( r )
#endif
        { }

        template< class ForwardRange2 >
        sub_range(
            const ForwardRange2& r,
            BOOST_DEDUCED_TYPENAME enable_if<
                is_compatible_range<const ForwardRange2>
            >::type* = 0
        ) : 

#if BOOST_WORKAROUND(BOOST_INTEL_CXX_VERSION, <= 800 )
            base( impl::adl_begin( r ), impl::adl_end( r ) )
#else
            base( r )
#endif
        { }

        template< class Iter >
        sub_range( Iter first, Iter last ) :
            base( first, last )
        { }

        template<class ForwardRange2>
        BOOST_DEDUCED_TYPENAME enable_if<
            is_compatible_range<ForwardRange2>,
            sub_range&
        >::type
        operator=(ForwardRange2& r)
        {
            base::operator=( r );
            return *this;
        }

        template<class ForwardRange2>
        BOOST_DEDUCED_TYPENAME enable_if<
            is_compatible_range<const ForwardRange2>,
            sub_range&
        >::type
        operator=( const ForwardRange2& r )
        {
            base::operator=( r );
            return *this;
        }   

        sub_range& operator=( const sub_range& r )
        {
            base::operator=( static_cast<const base&>(r) );
            return *this;            
        }
    };

} // namespace 'boost'

#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1500)) 
    #pragma warning( pop )
#endif

#endif

