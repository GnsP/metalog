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
    template<template<typename...> class term, typename lExpr, typename rExpr, typename u>
    struct unify<term<lExpr>, term<rExpr>, u> :
            unify<lExpr, rExpr, u>
    {};

    template<template<typename...> class term, typename lHExpr, typename lTExpr, typename rHExpr, typename rTExpr, typename u>
    struct unify<term<lHExpr, lTExpr>, term<rHExpr, rTExpr>, u> :
            boost::mpl::if_
            <
                unify<lHExpr, rHExpr, u>,
                unify<lTExpr, rTExpr, typename unify<lHExpr, rHExpr, u>::unifiers>,
                unify<lHExpr, rHExpr, u>
            >::type
    {};

    //{term(lExpr_1, lExpr_2, ..., lExpr_n-1, lExpr_n) = term(rExpr_1, rExpr_2, ..., rExpr_n-1, rExpr_n)} ==
    //    {_(lExpr_1, _(lExpr_2, _(..., _(lExpr_n-1, lExpr_n)))) = _(rExpr_1, _(rExpr_2, _(..., _(rExpr_n-1, rExpr_n))))}
    template
    <
            template<typename...> class term,
            typename lH1Expr, typename lH2Expr, typename lH3Expr, typename... lTExpr,
            typename rH1Expr, typename rH2Expr, typename rH3Expr, typename... rTExpr,
            typename u
    >
    struct unify<term<lH1Expr, lH2Expr, lH3Expr, lTExpr...>, term<rH1Expr, rH2Expr, rH3Expr, rTExpr...>, u> :
            unify<munify::term<lH1Expr, term<lH2Expr, lH3Expr, lTExpr...> >, munify::term<rH1Expr, term<rH2Expr, rH3Expr, rTExpr...> >, u>
    {};
}

#endif
