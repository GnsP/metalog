/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _METALOG_RESOLVE_CONTRADICTION_HPP_
#define _METALOG_RESOLVE_CONTRADICTION_HPP_

#include "../detail/preprocessor.hpp"

#include <boost/preprocessor/arithmetic/sub.hpp>

#include <boost/mpl/logical.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/pop_front.hpp>

namespace metalog
{
    template<typename hG, METALOG_VARIADIC_PARAMS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1), tG), typename clauses, typename it, typename s>
    struct resolve
            <
                conjunction<hG METALOG_TRAILING_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1), tG)>,
                clauses, it, it, s METALOG_TRAILING_VARIADIC_EMPTY_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1))
            > :
            boost::mpl::not_<boost::mpl::empty<typename boost::mpl::pop_front<s>::type> >
    {
        typedef typename boost::mpl::pop_front<s>::type solution;
    };
}

#endif
