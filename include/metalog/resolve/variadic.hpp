/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _METALOG_RESOLVE_VARIADIC_HPP_
#define _METALOG_RESOLVE_VARIADIC_HPP_

#include "../join.hpp"

#include "../detail/preprocessor.hpp"

#include <boost/preprocessor/arithmetic/sub.hpp>

namespace metalog
{
    template
    <
            typename goal, typename clauses, typename begin, typename end, typename s,
            METALOG_VARIADIC_PARAMS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1), sT)
    >
    struct resolve :
            resolve<goal, clauses, begin, end, typename join<s, METALOG_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1), sT)>::type>
    {};
}

#endif
