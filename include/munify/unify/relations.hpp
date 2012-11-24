/*
 * This file is part of munify, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _MUNIFY_RELATIONS_HPP_
#define _MUNIFY_RELATIONS_HPP_

#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>

namespace munify
{
    template<template<typename> class rel, typename lExpr, typename rExpr, typename u>
    struct unify<rel<lExpr>, rel<rExpr>, u> :
            public unify<lExpr, rExpr, u>
    {};

    template<template<typename> class rel, typename expr, typename u>
    struct unify<rel<expr>, rel<expr>, u> :
            public unifiable<boost::mpl::true_, u>
    {};

    template<template<typename, typename...> class rel, typename lHExpr, typename lTExpr, typename rHExpr, typename rTExpr, typename u>
    class unify<rel<lHExpr, lTExpr>, rel<rHExpr, rTExpr>, u> :
            public boost::mpl::if_
            <
                unify<lHExpr, rHExpr, u>,
                unify<lTExpr, rTExpr, typename unify<lHExpr, rHExpr, u>::unifiers>,
                unify<lHExpr, rHExpr, u>
            >::type
    {};

    template<template<typename, typename...> class rel, typename hExpr, typename lTExpr, typename rTExpr, typename u>
    struct unify<rel<hExpr, lTExpr>, rel<hExpr, rTExpr>, u> :
            public unify<lTExpr, rTExpr, u>
    {};

    template<template<typename, typename...> class rel, typename lHExpr, typename rHExpr, typename tExpr, typename u>
    struct unify<rel<lHExpr, tExpr>, rel<rHExpr, tExpr>, u> :
            public unify<lHExpr, rHExpr, u>
    {};

    template<template<typename, typename...> class rel, typename hExpr, typename tExpr, typename u>
    struct unify<rel<hExpr, tExpr>, rel<hExpr, tExpr>, u> :
            public unifiable<boost::mpl::true_, u>
    {};
}

#endif
