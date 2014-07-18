/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _METALOG_SEQUENCES_HPP_
#define _METALOG_SEQUENCES_HPP_

#include "../types.hpp"

#include "../detail/preprocessor.hpp"

#include <boost/preprocessor/arithmetic/sub.hpp>

#include <boost/mpl/identity.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/placeholders.hpp>

namespace metalog
{
    template<typename s1, typename s2>
    struct join<s1, s2 METALOG_TRAILING_VARIADIC_EMPTY_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 2))> :
            boost::mpl::fold<s2, s1, boost::mpl::insert<boost::mpl::_1, boost::mpl::end<boost::mpl::_1>, boost::mpl::_2> >
    {};

    template<typename s1, typename s2, METALOG_VARIADIC_PARAMS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 2), sT)>
    struct join :
            join
            <
                typename boost::mpl::fold<s2, s1, boost::mpl::insert<boost::mpl::_1, boost::mpl::end<boost::mpl::_1>, boost::mpl::_2> >::type,
                METALOG_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 2), sT)
            >
    {};
}

#endif
