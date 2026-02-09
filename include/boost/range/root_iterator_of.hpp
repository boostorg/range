//  Copyright Klaus Triendl 2020. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//
// For more information, see http://www.boost.org/libs/range/
//
#if defined(_MSC_VER)
#pragma once
#endif

#ifndef BOOST_RANGE_ROOT_ITERATOR_OF_HPP_INCLUDED
#define BOOST_RANGE_ROOT_ITERATOR_OF_HPP_INCLUDED

#include <boost/config.hpp> // BOOST_DEDUCED_TYPENAME
#include <boost/mpl/has_xxx.hpp>
#include <boost/range/iterator_range.hpp>


namespace boost
{

    namespace range_detail
    {

        BOOST_MPL_HAS_XXX_TRAIT_DEF(base_type)

        template<typename It, bool B = has_base_type<It>::value>
        struct root_iterator_of_impl;

        template<typename It>
        struct root_iterator_of_impl<It, false>
        {
            typedef It type;
        };

        template<typename It>
        struct root_iterator_of_impl<It, true> :
            root_iterator_of_impl<BOOST_DEDUCED_TYPENAME It::base_type>
        {};

        template<typename It>
        It root_of(It it, boost::mpl::bool_<false>)
        {
            return it;
        }
        template<typename It>
        BOOST_DEDUCED_TYPENAME root_iterator_of_impl<It, true>::type
            root_of(It it, boost::mpl::bool_<true>)
        {
            return root_of(it.base());
        }

    }

    namespace range
    {

        template<typename It>
        struct root_iterator_of :
            range_detail::root_iterator_of_impl<It>
        {};

#ifdef __cpp_alias_templates
        template<typename It>
        using root_iterator_of_t = typename root_iterator_of<It>::type;
#endif

        template<typename It>
        BOOST_DEDUCED_TYPENAME root_iterator_of<It>::type
            root_of(It it)
        {
            return range_detail::root_of( it,
                                          BOOST_DEDUCED_TYPENAME range_detail::has_base_type<It>::type{} );
        }

        template<typename It>
        iterator_range<BOOST_DEDUCED_TYPENAME root_iterator_of<It>::type>
            root_of(iterator_range<It> rng)
        {
            return make_iterator_range(root_of(rng.begin()), root_of(rng.end()));
        }

    }
    using range::root_iterator_of;
    using range::root_of;

}

#endif // include guard
