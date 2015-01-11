/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _METALOG_JOIN_SEQUENCES_HPP_
#define _METALOG_JOIN_SEQUENCES_HPP_

#include <boost/mpl/insert.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/placeholders.hpp>

namespace metalog
{
    template<typename seq1, typename seq2>
    struct join<seq1, seq2> :
            boost::mpl::fold<seq2, seq1, boost::mpl::insert<boost::mpl::_1, boost::mpl::end<boost::mpl::_1>, boost::mpl::_2> >
    {};
}

#endif
