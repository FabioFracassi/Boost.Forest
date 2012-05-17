//-------------------------------------------------------------------------------------------------
// Boost.Forest library
//
// Copyright 2012 Fabio Fracassi
//
// Distributed under the Boost Software License Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
//-------------------------------------------------------------------------------------------------
// Ported over from ASL during C++Now! Library in a week session with permission from Sean Parent
//-------------------------------------------------------------------------------------------------
/*
    Copyright 2005-2008 Adobe Systems Incorporated
    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or a copy at http://stlab.adobe.com/licenses.html)
*/
//-------------------------------------------------------------------------------------------------

#ifndef ADOBE_ITERATOR_SET_NEXT_HPP
#define ADOBE_ITERATOR_SET_NEXT_HPP

#include <boost/next_prior.hpp>

/*************************************************************************************************/

namespace boost {

namespace forest {

namespace detail {

/*! \addtogroup adobe_iterator
@{
*/

/*
Example:

template <>
stuct set_next_fn<T>
{
    void operator()(T x, T y) const
    {
    //...
    }
};
*/

template <typename I> // I models NodeIterator
struct set_next_fn; // Must be specialized

/*************************************************************************************************/

template <typename I> // I models NodeIterator
inline void set_next(I x, I y)
{
    set_next_fn<I>()(x, y);
}

/*************************************************************************************************/

/*
    location: a valid forward node iterator
    first and last - two valid node iterators
    
    postcondition: location->first...last->next(location)
*/

template <typename I> // T models ForwardNodeIterator
inline void splice_node_range(I location, I first, I last)
{
    I successor(boost::next(location));
    set_next(location, first);
    set_next(last, successor);
}

template <typename I> // I models ForwardNodeIterator
inline void skip_next_node(I location)
{ set_next(location, boost::next(boost::next(location))); }

template <typename I> // I models BidirectionalNodeIterator
inline void skip_node(I location)
{ set_next(boost::prior(location), boost::next(location)); }

//!@}

/*************************************************************************************************/

} // namespace detail
} // namespace forest
} // namespace adobe

/*************************************************************************************************/

// ADOBE_ITERATOR_SET_NEXT_HPP
#endif
