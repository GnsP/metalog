/*
 * This file is part of munify, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _MUNIFY_EQUIV_TRANSFORM_HPP_
#define _MUNIFY_EQUIV_TRANSFORM_HPP_

namespace munify
{
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
