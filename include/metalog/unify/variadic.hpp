/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _METALOG_UNIFY_VARIADIC_HPP_
#define _METALOG_UNIFY_VARIADIC_HPP_

#include "../preprocessor.hpp"

#include <boost/preprocessor/arithmetic/sub.hpp>

namespace metalog
{
    template
    <
            typename lExpr, typename rExpr, typename uH,
            METALOG_VARIADIC_PARAMS(BOOST_PP_SUB(METALOG_MAX_ARGS, 1), uT)
    >
    struct unify :
            unify
            <
                lExpr, rExpr,
                unifiers<uH, METALOG_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_ARGS, 1), uT)>
            >
    {};
}

#endif
