//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2009.
// (C) Copyright Adam Wulkiewicz 2014.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_MOVE_TEST_COPYMOVABLE_HPP
#define BOOST_MOVE_TEST_COPYMOVABLE_HPP

#include <boost/move/detail/config_begin.hpp>

//[movable_definition 
//header file "copy_movable.hpp"
#include <boost/move/core.hpp>

#include <ostream>

//A copy_movable class
class copy_movable
{
   BOOST_COPYABLE_AND_MOVABLE(copy_movable)
   int value_;

   public:
   copy_movable(int v = 1) : value_(v) { BOOST_ASSERT(v > 0); }

   //Move constructor and assignment
   copy_movable(BOOST_RV_REF(copy_movable) m)
   {  value_ = m.value_;   m.value_ = 0; }

   copy_movable(const copy_movable & m)
   {  value_ = m.value_;  }

   copy_movable & operator=(BOOST_RV_REF(copy_movable) m)
   {  value_ = m.value_;   m.value_ = 0;  return *this;  }

   copy_movable & operator=(BOOST_COPY_ASSIGN_REF(copy_movable) m)
   {  value_ = m.value_;   return *this;  }

   bool moved() const //Observer
   {  return value_ == 0; }

   friend bool operator==(copy_movable const& l, copy_movable const& r)
   {  return l.value_ == r.value_; }

   friend bool operator!=(copy_movable const& l, copy_movable const& r)
   {  return l.value_ != r.value_; }

   friend bool operator<(copy_movable const& l, copy_movable const& r)
   {  return l.value_ < r.value_; }

   friend std::ostream & operator<<(std::ostream & os, copy_movable const& r)
   {  return os << (r.moved() ? " moved" : " not moved"); }
};

//]

#include <boost/move/detail/config_end.hpp>

#endif //BOOST_MOVE_TEST_COPYMOVABLE_HPP
