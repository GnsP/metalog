/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _METALOG_UNIFY_TERMS_HPP_
#define _METALOG_UNIFY_TERMS_HPP_

#include "../detail/preprocessor.hpp"

#include <boost/config.hpp>

#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

#include <boost/mpl/if.hpp>

namespace metalog
{
    template<typename lExpr, typename rExpr, typename u>
    struct unify
            <
                term<lExpr METALOG_TRAILING_VARIADIC_EMPTY_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1))>,
                term<rExpr METALOG_TRAILING_VARIADIC_EMPTY_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1))>,
                u METALOG_TRAILING_VARIADIC_EMPTY_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1))
            > :
            unify<lExpr, rExpr, u>
    {};

    template<typename lHExpr, typename lTExpr, typename rHExpr, typename rTExpr, typename u>
    struct
            unify
            <
                term<lHExpr, lTExpr METALOG_TRAILING_VARIADIC_EMPTY_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 2))>,
                term<rHExpr, rTExpr METALOG_TRAILING_VARIADIC_EMPTY_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 2))>,
                u METALOG_TRAILING_VARIADIC_EMPTY_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1))
            > :
            boost::mpl::if_
            <
                unify<lHExpr, rHExpr, u>,
                unify<lTExpr, rTExpr, typename unifiers<unify<lHExpr, rHExpr, u> >::type>,
                unify<lHExpr, rHExpr, u>
            >::type
    {};

    template<template<METALOG_VARIADIC_PARAMS(1, _)> class term, typename lExpr, typename rExpr, typename u>
    struct unify<term<lExpr>, term<rExpr>, u METALOG_TRAILING_VARIADIC_EMPTY_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1))> :
            unify<lExpr, rExpr, u>
    {};

//{term(lExpr_1, lExpr_2, ..., lExpr_n-1, lExpr_n) = term(rExpr_1, rExpr_2, ..., rExpr_n-1, rExpr_n)} ==
//    {_(lExpr_1, _(lExpr_2, _(..., _(lExpr_n-1, lExpr_n)))) = _(rExpr_1, _(rExpr_2, _(..., _(rExpr_n-1, rExpr_n))))}
#define METALOG_DEFINE_EQUIVALENCE_TRANSFORM(N) \
    BOOST_PP_ASSERT(BOOST_PP_LESS_EQUAL(2, N)) \
    template \
    < \
            template<METALOG_VARIADIC_PARAMS(N, _)> class term, \
            typename lH1Expr, typename lH2Expr METALOG_TRAILING_VARIADIC_PARAMS(BOOST_PP_SUB(N, 2), lTExpr), \
            typename rH1Expr, typename rH2Expr METALOG_TRAILING_VARIADIC_PARAMS(BOOST_PP_SUB(N, 2), rTExpr), \
            typename u \
    > \
    struct unify \
    < \
        term<lH1Expr, lH2Expr METALOG_TRAILING_VARIADIC_ARGS(BOOST_PP_SUB(N, 2), lTExpr)>, \
        term<rH1Expr, rH2Expr METALOG_TRAILING_VARIADIC_ARGS(BOOST_PP_SUB(N, 2), rTExpr)>, \
        u METALOG_TRAILING_VARIADIC_EMPTY_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1)) \
    > : \
            unify \
            < \
                metalog::term<lH1Expr, metalog::term<lH2Expr METALOG_TRAILING_VARIADIC_ARGS(BOOST_PP_SUB(N, 2), lTExpr)> >, \
                metalog::term<rH1Expr, metalog::term<rH2Expr METALOG_TRAILING_VARIADIC_ARGS(BOOST_PP_SUB(N, 2), rTExpr)> >, \
                u \
            > \
    {};

#ifdef BOOST_NO_CXX11_VARIADIC_TEMPLATES

#define METALOG_FORWARD_DEFINE_EQUIVALENCE_TRANSFORM(Z, N, DATA) \
    METALOG_DEFINE_EQUIVALENCE_TRANSFORM(N)

    BOOST_PP_REPEAT_FROM_TO(2, METALOG_MAX_VARIADIC_ARGS, METALOG_FORWARD_DEFINE_EQUIVALENCE_TRANSFORM, _)
#endif

METALOG_DEFINE_EQUIVALENCE_TRANSFORM(METALOG_MAX_VARIADIC_ARGS)

}

#endif
