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
}

#endif
