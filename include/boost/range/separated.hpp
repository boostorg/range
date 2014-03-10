// Boost.Range library
//
//  Copyright Neil Groves 2014.
//  Use, modification and distribution is subject to the Boost Software
//  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//
#ifndef BOOST_RANGE_SEPARATED_HPP_INCLUDED
#define BOOST_RANGE_SEPARATED_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/range/concepts.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator.hpp>
#include <ostream>

namespace boost
{
    namespace range_detail
    {

template<typename Iter, typename Separator>
class output_stream_writer
{
public:
    output_stream_writer(Iter first, Iter last, Separator separator)
        : m_first(first)
        , m_last(last)
        , m_separator(separator)
    {
    }

    template<typename OStream>
    void write(OStream& out) const
    {
        write_impl(out, m_first, m_last, m_separator);
    }

private:
    template<typename OStream>
    static void write_impl(
            OStream& out, Iter first, Iter last, Separator separator)
    {
        if (first != last)
        {
            out << *first;
            for (++first; first != last; ++first)
            {
                out << separator << *first;
            }
        }
    }

    Iter m_first;
    Iter m_last;
    Separator m_separator;
};

template<typename Char, typename Traits, typename Iter, typename Separator>
std::basic_ostream<Char, Traits>&
operator<<(
        std::basic_ostream<Char, Traits>& out,
        const output_stream_writer<Iter, Separator>& writer)
{
    writer.write(out);
    return out;
}

    } // namespace range_detail

    namespace range
    {

template<typename Range, typename Separator>
inline range_detail::output_stream_writer<
    typename range_iterator<const Range>::type,
    Separator
>
separated(const Range& rng, Separator separator)
{
    BOOST_RANGE_CONCEPT_ASSERT((SinglePassRangeConcept<const Range>));
    return range_detail::output_stream_writer<
            typename range_iterator<const Range>::type,
            Separator
    >(boost::begin(rng), boost::end(rng), separator);
}

    } // namespace range
} // namespace boost

#endif // include guard
