/*
    Copyright 2005-2007 Adobe Systems Incorporated
    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or a copy at http://stlab.adobe.com/licenses.html)
*/
/*************************************************************************************************/

#ifndef ADOBE_ALGORITHM_REVERSE_HPP
#define ADOBE_ALGORITHM_REVERSE_HPP

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator.hpp>

#include <boost/forest/detail/iterator/set_next.hpp>

#include <algorithm>
#include <utility>

/*************************************************************************************************/

namespace boost {
namespace forest {

/*************************************************************************************************/
/*!
\defgroup reverse reverse
\ingroup mutating_algorithm

\see
    - STL documentation for \ref stldoc_reverse
    - STL documentation for \ref stldoc_reverse_copy
*/
/*************************************************************************************************/

namespace detail {

/*************************************************************************************************/

/*!
\ingroup node_algorithm
*/
template <typename I> // I models NodeIterator
I reverse_append(I first, I last, I result)
{
    while (first != last)
    {
        I prior(first);
        ++first;
        boost::forest::detail::set_next(prior, result);
        result = prior;
    }
    return result;
}

/*!
\ingroup node_algorithm
*/
template <typename R, // R models NodeRange
          typename I> // I models NodeIterator
inline I reverse_append(R& range, I result)
{
    return boost::forest::detail::reverse_append(boost::begin(range), boost::end(range), result);
}

/*!
\ingroup node_algorithm
*/
template <typename I> // I models NodeIterator
inline I reverse_nodes(I first, I last)
{
    return boost::forest::detail::reverse_append(first, last, last);
}

/*!
\ingroup node_algorithm
*/
template <typename R> // R models NodeRange
inline typename boost::range_iterator<R>::type reverse_nodes(R& range)
{
    return boost::forest::detail::reverse_nodes(boost::begin(range), boost::end(range));
}

/*************************************************************************************************/

} // namspace detail

/*************************************************************************************************/
/*!
    \ingroup reverse

    \brief reverse implementation
*/
template <class BidirectionalRange>
inline void reverse(BidirectionalRange& range)
{
    std::reverse(boost::begin(range), boost::end(range));
}

/*!
    \ingroup reverse

    \brief reverse implementation
*/
template <class BidirectionalRange, class OutputIterator>
inline void reverse_copy(BidirectionalRange& range, OutputIterator result)
{
    std::reverse_copy(boost::begin(range), boost::end(range), result);
}

/*!
    \ingroup reverse

    \brief reverse implementation
*/
template <class BidirectionalRange, class OutputIterator>
inline void reverse_copy(const BidirectionalRange& range, OutputIterator result)
{
    std::reverse_copy(boost::begin(range), boost::end(range), result);
}

/*************************************************************************************************/
/*!
    \ingroup reverse

    \brief reverse implementation
*/
template <typename I> // I models Bidirectional Iterator
std::pair<I, I> reverse_until(I f, I m, I l)
{
    while (f != m && m != l)
    {
        --l;

        std::iter_swap(f, l);

        ++f;
    }

    return std::pair<I, I>(f, l);
} 
 
/*************************************************************************************************/

} // namespace forest
} // namespace boost

/*************************************************************************************************/

#endif

/*************************************************************************************************/
