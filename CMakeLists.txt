# Copyright 2019 Sam Day
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt
#
# NOTE: CMake support for Boost.range is currently experimental at best
#       and the interface is likely to change in the future

cmake_minimum_required(VERSION 3.5)
project(BoostRange LANGUAGES CXX)

add_library(boost_range INTERFACE)
add_library(Boost::range ALIAS boost_range)

target_include_directories(boost_range INTERFACE include)

target_link_libraries(boost_range
        INTERFACE
        Boost::array
        Boost::assert
        Boost::concept_check
        Boost::config
        Boost::core
        Boost::detail
        Boost::functional
        Boost::iterator
        Boost::mpl
        Boost::numeric_conversion
        Boost::optional
        Boost::preprocessor
        Boost::regex
        Boost::static_assert
        Boost::tuple
        Boost::type_traits
        Boost::utility
        )
