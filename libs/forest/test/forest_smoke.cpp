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

#include <iostream>
#include <limits>
#include <new>
#include <cassert>

#include <boost/range/algorithm/find.hpp>
#include <boost/forest/forest.hpp>
#include <boost/range.hpp>

template <typename R> // R is a depth adaptor range
void output(const R& f)
{
    typedef typename boost::range_iterator<R>::type iterator;

    for (iterator first(boost::begin(f)), last(boost::end(f)); first != last; ++first)
    {
        for (typename iterator::difference_type i(first.depth()); i != 0; --i)
        {
            std::cout << "\t";
        }
        if (first.edge() == boost::forest::forest_leading_edge)
        {
            std::cout << "<" << *first << ">" << std::endl;
        }
        else
        {
            std::cout << "</" << *first << ">" << std::endl;
        }
    }
}
    
int main()
{
    typedef boost::forest::forest<std::string> forest;
    typedef forest::iterator iterator;

    std::cout << "<- default construction and insert ->" << std::endl;
    forest f;
    iterator i (f.begin());
    i = boost::forest::trailing_of(f.insert(i, "grandmother"));
    {
        iterator p (boost::forest::trailing_of(f.insert(i, "mother")));
        f.insert(p, "me");
        f.insert(p, "sister");
        f.insert(p, "brother");
    }
    {
        iterator p (boost::forest::trailing_of(f.insert(i, "aunt")));
        f.insert(p, "cousin");
    }
    f.insert(i, "uncle");
    
    output(boost::forest::depth_range(f));
    std::cout << "<- copy construction and reverse ->" << std::endl;
    
    forest f2(f);
    iterator f2_grandmother(boost::find(boost::forest::preorder_range(f2), "grandmother").base());
    f2.reverse(boost::forest::child_begin(f2_grandmother), boost::forest::child_end(f2_grandmother));
    
    output(boost::forest::depth_range(f2));
    
    std::cout << "<- reverse iterator ->" << std::endl;
    
    output(boost::forest::depth_range(boost::forest::reverse_fullorder_range(f)));

    std::cout << "<- node deletion ->" << std::endl;
    
    forest f3(f);
    iterator f3_aunt(boost::find(boost::forest::preorder_range(f3), "aunt").base());
    iterator f3_uncle(boost::find(boost::forest::preorder_range(f3), "uncle").base());
    f3.erase(boost::forest::leading_of(f3_aunt), ++(boost::forest::trailing_of(f3_uncle)));

    output(boost::forest::depth_range(f3));

    std::cout << "<- splicing 1 ->" << std::endl;

    forest f4(f);
    forest f5(f);
    iterator f4_aunt(boost::find(boost::forest::preorder_range(f4), "aunt").base());

    std::cout << "Size of f4 pre-splice: " << static_cast<unsigned long>(f4.size()) << std::endl;
    std::cout << "Size of f5 pre-splice: " << static_cast<unsigned long>(f5.size()) << std::endl;

    // Note that because f4_aunt is on the leading edge, the spliced forest's
    // top nodes will be siblings to f4_aunt.

    f4.splice(f4_aunt, f5);    

    output(boost::forest::depth_range(f4));

    std::cout << "Size of f4 post-splice: " << static_cast<unsigned long>(f4.size()) << std::endl;
    std::cout << "Size of f5 post-splice: " << static_cast<unsigned long>(f5.size()) << std::endl;

    std::cout << "<- splicing 2 ->" << std::endl;

    forest f6(f);
    forest f7(f);
    iterator f6_aunt(boost::find(boost::forest::preorder_range(f6), "aunt").base());

    std::cout << "Size of f6 pre-splice: " << static_cast<unsigned long>(f6.size()) << std::endl;
    std::cout << "Size of f7 pre-splice: " << static_cast<unsigned long>(f7.size()) << std::endl;

    f6_aunt = boost::forest::trailing_of(f6_aunt);

    // Note that because f6_aunt is on the trailing edge, the spliced forest's
    // top nodes will be children to f6_aunt.

    f6.splice(f6_aunt, f7);    

    output(boost::forest::depth_range(f6));

    std::cout << "Size of f6 post-splice: " << static_cast<unsigned long>(f6.size()) << std::endl;
    std::cout << "Size of f7 post-splice: " << static_cast<unsigned long>(f7.size()) << std::endl;

    return 0;
}
