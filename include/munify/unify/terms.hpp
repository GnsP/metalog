/*
 * This file is part of munify, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _MUNIFY_UNIFY_TERMS_HPP_
#define _MUNIFY_UNIFY_TERMS_HPP_

#include "../types.hpp"
#include "munify/detail/preprocessor.hpp"

#include <boost/config.hpp>
#include <boost/preprocessor/debug/assert.hpp>
#include <boost/preprocessor/comparison/less_equal.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>

namespace munify
{
    template<template<MUNIFY_VARIADIC_PARAMS(1, _)> class term, typename lExpr, typename rExpr, typename u>
    struct unify<term<lExpr>, term<rExpr>, u> :
            unify<lExpr, rExpr, u>
    {};

    template<typename lExpr, typename rExpr, typename u>
    struct
            unify
            <
                term<lExpr MUNIFY_TRAILING_VARIADIC_EMPTY_ARGS(BOOST_PP_SUB(MUNIFY_MAX_VARIADIC_ARGS, 1))>,
                term<rExpr MUNIFY_TRAILING_VARIADIC_EMPTY_ARGS(BOOST_PP_SUB(MUNIFY_MAX_VARIADIC_ARGS, 1))>,
                u
            > :
            unify<lExpr, rExpr, u>
    {};

    template<template<MUNIFY_VARIADIC_PARAMS(2, _)> class term,
             typename lHExpr, typename lTExpr, typename rHExpr, typename rTExpr, typename u>
    struct unify<term<lHExpr, lTExpr>, term<rHExpr, rTExpr>, u> :
            boost::mpl::if_
            <
                unify<lHExpr, rHExpr, u>,
                unify<lTExpr, rTExpr, typename unify<lHExpr, rHExpr, u>::unifiers>,
                unify<lHExpr, rHExpr, u>
            >::type
    {};

    template<typename lHExpr, typename lTExpr, typename rHExpr, typename rTExpr, typename u>
    struct
            unify
            <
                term<lHExpr, lTExpr MUNIFY_TRAILING_VARIADIC_EMPTY_ARGS(BOOST_PP_SUB(MUNIFY_MAX_VARIADIC_ARGS, 2))>,
                term<rHExpr, rTExpr MUNIFY_TRAILING_VARIADIC_EMPTY_ARGS(BOOST_PP_SUB(MUNIFY_MAX_VARIADIC_ARGS, 2))>,
                u
            > :
            boost::mpl::if_
            <
                unify<lHExpr, rHExpr, u>,
                unify<lTExpr, rTExpr, typename unify<lHExpr, rHExpr, u>::unifiers>,
                unify<lHExpr, rHExpr, u>
            >::type
    {};

//{term(lExpr_1, lExpr_2, ..., lExpr_n-1, lExpr_n) = term(rExpr_1, rExpr_2, ..., rExpr_n-1, rExpr_n)} ==
//    {_(lExpr_1, _(lExpr_2, _(..., _(lExpr_n-1, lExpr_n)))) = _(rExpr_1, _(rExpr_2, _(..., _(rExpr_n-1, rExpr_n))))}
#define MUNIFY_DEFINE_EQUIVALENCE_TRANSFORM(N) \
    BOOST_PP_ASSERT(BOOST_PP_LESS_EQUAL(3, N)) \
    template \
    < \
            template<MUNIFY_VARIADIC_PARAMS(N, _)> class term, \
            typename lH1Expr, typename lH2Expr, typename lH3Expr MUNIFY_TRAILING_VARIADIC_PARAMS(BOOST_PP_SUB(N, 3), lTExpr), \
            typename rH1Expr, typename rH2Expr, typename rH3Expr MUNIFY_TRAILING_VARIADIC_PARAMS(BOOST_PP_SUB(N, 3), rTExpr), \
            typename u \
    > \
    struct unify \
    < \
        term<lH1Expr, lH2Expr, lH3Expr MUNIFY_TRAILING_VARIADIC_ARGS(BOOST_PP_SUB(N, 3), lTExpr)>, \
        term<rH1Expr, rH2Expr, rH3Expr MUNIFY_TRAILING_VARIADIC_ARGS(BOOST_PP_SUB(N, 3), rTExpr)>, \
        u \
    > : \
            unify \
            < \
                munify::term<lH1Expr, munify::term<lH2Expr, lH3Expr MUNIFY_TRAILING_VARIADIC_ARGS(BOOST_PP_SUB(N, 3), lTExpr)> >, \
                munify::term<rH1Expr, munify::term<rH2Expr, rH3Expr MUNIFY_TRAILING_VARIADIC_ARGS(BOOST_PP_SUB(N, 3), rTExpr)> >, \
                u \
            > \
    {};

#ifdef BOOST_NO_CXX11_VARIADIC_TEMPLATES

#define MUNIFY_FORWARD_DEFINE_EQUIVALENCE_TRANSFORM(Z, N, DATA) \
    MUNIFY_DEFINE_EQUIVALENCE_TRANSFORM(N)

    BOOST_PP_REPEAT_FROM_TO(3, MUNIFY_MAX_VARIADIC_ARGS, MUNIFY_FORWARD_DEFINE_EQUIVALENCE_TRANSFORM, _)
#endif

MUNIFY_DEFINE_EQUIVALENCE_TRANSFORM(MUNIFY_MAX_VARIADIC_ARGS)

}

#endif
