/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _METALOG_UNIFY_TERMS_HPP_
#define _METALOG_UNIFY_TERMS_HPP_

#include "../term.hpp"

#include <boost/config.hpp>

#include <boost/preprocessor/repetition/repeat_from_to.hpp>

#include <boost/mpl/if.hpp>

//{term(lExpr_1, lExpr_2, ..., lExpr_n-1, lExpr_n) = term(rExpr_1, rExpr_2, ..., rExpr_n-1, rExpr_n)} ==
//    {_(lExpr_1, _(lExpr_2, _(..., _(lExpr_n-1, lExpr_n)))) = _(rExpr_1, _(rExpr_2, _(..., _(rExpr_n-1, rExpr_n))))}
#define METALOG_DEFINE_EQUIVALENCE_TRANSFORM(N) \
    BOOST_PP_ASSERT(BOOST_PP_LESS_EQUAL(1, N)) \
    template \
    < \
            template<METALOG_VARIADIC_PARAMS(N, _)> class term, \
            METALOG_VARIADIC_PARAMS(N, exprsL), METALOG_VARIADIC_PARAMS(N, exprsR), typename u \
    > \
    struct unify<term<METALOG_VARIADIC_ARGS(N, exprsL)>, term<METALOG_VARIADIC_ARGS(N, exprsR)>, u> : \
            unify \
            < \
                typename metalog::term<METALOG_VARIADIC_ARGS(N, exprsL)>::type, \
                typename metalog::term<METALOG_VARIADIC_ARGS(N, exprsR)>::type, \
                u \
            > \
    {};

#define METALOG_FORWARD_DEFINE_EQUIVALENCE_TRANSFORM(Z, N, DATA) \
    METALOG_DEFINE_EQUIVALENCE_TRANSFORM(N)

namespace metalog
{
    template<typename lExpr, typename rExpr, typename u>
    struct unify<term<lExpr>, term<rExpr>, u> :
            unify<lExpr, rExpr, u>
    {};

    template<typename exprHL, typename exprTL, typename exprHR, typename exprTR, typename u>
    struct unify<term<exprHL, exprTL>, term<exprHR, exprTR>, u> :
            boost::mpl::if_
            <
                unify<exprHL, exprHR, u>,
                unify<exprTL, exprTR, unify<exprHL, exprHR, u> >,
                unify<exprHL, exprHR, u>
            >::type
    {};

#ifdef BOOST_NO_CXX11_VARIADIC_TEMPLATES
    BOOST_PP_REPEAT_FROM_TO(1, METALOG_MAX_ARGS, METALOG_FORWARD_DEFINE_EQUIVALENCE_TRANSFORM, _)
#endif

    METALOG_DEFINE_EQUIVALENCE_TRANSFORM(METALOG_MAX_ARGS)
}

#undef METALOG_DEFINE_EQUIVALENCE_TRANSFORM
#undef METALOG_FORWARD_DEFINE_EQUIVALENCE_TRANSFORM

#endif
