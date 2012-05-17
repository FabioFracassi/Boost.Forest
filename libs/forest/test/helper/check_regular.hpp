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

#include <boost/test/test_case_template.hpp>

namespace boost {
namespace forest {
namespace test {

/*!
\addtogroup testing
@{
*/

template <typename T>
T arbitrary_regular_value();


template <typename T>
void check_regular(const T& x)
{
    using std::swap;

    BOOST_CHECK(x != T());
    T y = x;
    BOOST_CHECK_MESSAGE(x == y, "copy-ctor");
    T z = T();
    BOOST_CHECK_MESSAGE(z != x, "default-ctor");
    z = y;
    BOOST_CHECK_MESSAGE(x == z, "assignment");
    T w = T();
    swap(y, w);
    BOOST_CHECK(x == w && x != y && y == T());
}


BOOST_TEST_CASE_TEMPLATE_FUNCTION(check_regulars, T)
{
    check_regular(arbitrary_regular_value<T>());
}

}
}
}

//! @}
