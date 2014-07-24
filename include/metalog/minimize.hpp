/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _METALOG_MINIMIZE_HPP_
#define _METALOG_MINIMIZE_HPP_

#include "types.hpp"
#include "substitute.hpp"

#include <boost/mpl/map.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/mpl/placeholders.hpp>

namespace metalog
{
    template<typename unifiers>
    struct minimize :
            boost::mpl::fold
            <
                unifiers,
                boost::mpl::map<>,
                bind
                <
                    boost::mpl::_1,
                    boost::mpl::first<boost::mpl::_2>,
                    boost::mpl::apply_wrap1<substitute<unifiers>, boost::mpl::second<boost::mpl::_2> >
                >
            >
    {};
}

#endif
