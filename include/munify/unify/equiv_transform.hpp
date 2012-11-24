/*
 * This file is part of munify, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _MUNIFY_EQUIV_TRANSFORM_HPP_
#define _MUNIFY_EQUIV_TRANSFORM_HPP_

#include <boost/tuple/tuple.hpp>

namespace munify
{
    //{lRel(lExpr_1, lExpr_2, ..., lExpr_n-1, lExpr_n) = rRel(rExpr_1, rExpr_2, ..., rExpr_n-1, rExpr_n)} ==
    //    {lRel(lExpr_1, _(lExpr_2, _(..., _(lExpr_n-1, lExpr_n)))) = rRel(rExpr_1, _(rExpr_2, _(..., _(rExpr_n-1, rExpr_n))))}
    template<template<typename, typename...> class lRel, typename lHExpr, typename... lTExpr, template<typename, typename...> class rRel, typename rHExpr, typename... rTExpr, typename u>
    struct unify<lRel<lHExpr, lTExpr...>, rRel<rHExpr, rTExpr...>, u> :
            public unify<lRel<lHExpr, boost::tuples::tuple<lTExpr...> >, rRel<rHExpr, boost::tuples::tuple<rTExpr...> >, u>
    {};
}

#endif
