// Boost.Range library
//
// (C) Copyright Ion Gaztanaga 2012
// (C) Copyright Adam Wulkiewicz 2014
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_RANGE_DETAIL_MOVE_ITERATOR_HPP
#define BOOST_RANGE_DETAIL_MOVE_ITERATOR_HPP

#include <boost/move.hpp>

namespace boost {

namespace range_detail {

template <class It>
class move_iterator
{
public:
   typedef typename std::input_iterator_tag iterator_category;

   typedef It                                                              iterator_type;
   typedef typename std::iterator_traits<iterator_type>::value_type        value_type;
   typedef It                                                              pointer;
   typedef typename std::iterator_traits<iterator_type>::difference_type   difference_type;

   #if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
   typedef value_type &&                                                   reference;
   #else
   typedef typename ::boost::move_detail::if_
      < ::boost::has_move_emulation_enabled<value_type>
      , ::boost::rv<value_type>&
      , value_type & >::type                                               reference;
   #endif

   move_iterator()
   {}

   explicit move_iterator(It i)
      :  m_it(i)
   {}

   template <class U>
   move_iterator(const move_iterator<U>& u)
      :  m_it(u.base())
   {}

   iterator_type base() const
   {  return m_it;   }

   reference operator*() const
   {
      #if defined(BOOST_NO_CXX11_RVALUE_REFERENCES) || defined(BOOST_MOVE_OLD_RVALUE_REF_BINDING_RULES)
      return *m_it;
      #else
      return ::boost::move(*m_it);
      #endif
   }

   pointer   operator->() const
   {  return m_it;   }

   move_iterator& operator++()
   {  ++m_it; return *this;   }

   move_iterator<iterator_type>  operator++(int)
   {  move_iterator<iterator_type> tmp(*this); ++(*this); return tmp;   }

   friend bool operator==(const move_iterator& x, const move_iterator& y)
   {  return x.base() == y.base();  }

   friend bool operator!=(const move_iterator& x, const move_iterator& y)
   {  return x.base() != y.base();  }

private:
   It m_it;
};

template<class It>
inline move_iterator<It> make_move_iterator(const It &it)
{  return move_iterator<It>(it); }

} // namespace range_detail

namespace move_detail {

template <class I>
struct is_move_iterator< ::boost::range::detail::move_iterator<I> >
   : public ::boost::move_detail::integral_constant<bool, true>
{
};

}  // namespace move_detail

}  //namespace boost

#endif //#ifndef BOOST_RANGE_DETAIL_MOVE_ITERATOR_HPP
