/*
 * This file is part of munify, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _MUNIFY_TERMS_HPP_
#define _MUNIFY_TERMS_HPP_

#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>

namespace munify
{
    template<template<typename, typename...> class term, typename lExpr, typename rExpr, typename u>
    struct unify<term<lExpr>, term<rExpr>, u> :
            public unify<lExpr, rExpr, u>
    {};

    template<template<typename, typename...> class term, typename lHExpr, typename lTExpr, typename rHExpr, typename rTExpr, typename u>
    class unify<term<lHExpr, lTExpr>, term<rHExpr, rTExpr>, u> :
            public boost::mpl::if_
            <
                unify<lHExpr, rHExpr, u>,
                unify<lTExpr, rTExpr, typename unify<lHExpr, rHExpr, u>::unifiers>,
                unify<lHExpr, rHExpr, u>
            >::type
    {};

    //{lTerm(lExpr_1, lExpr_2, ..., lExpr_n-1, lExpr_n) = rTerm(rExpr_1, rExpr_2, ..., rExpr_n-1, rExpr_n)} ==
    //    {lTerm(lExpr_1, _(lExpr_2, _(..., _(lExpr_n-1, lExpr_n)))) = rTerm(rExpr_1, _(rExpr_2, _(..., _(rExpr_n-1, rExpr_n))))}
    template
    <
            template<typename, typename, typename...> class lTerm, typename lH1Expr, typename lH2Expr, typename... lTExpr,
            template<typename, typename, typename...> class rTerm, typename rH1Expr, typename rH2Expr, typename... rTExpr,
            typename u
    >
    struct unify<lTerm<lH1Expr, lH2Expr, lTExpr...>, rTerm<rH1Expr, rH2Expr, rTExpr...>, u> :
            public unify<lTerm<lH1Expr, term<lH2Expr, lTExpr...> >, rTerm<rH1Expr, term<rH2Expr, rTExpr...> >, u>
    {};
}

#endif
