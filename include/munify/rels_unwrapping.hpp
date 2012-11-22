/*
 * This file is part of munify, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _MUNIFY_RELS_UNWRAPPING_HPP_
#define _MUNIFY_RELS_UNWRAPPING_HPP_

#include "unify.hpp"

#include <boost/mpl/bool.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/map.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/insert.hpp>

namespace munify
{
    template<template<typename> class rel, typename lExpr, typename rExpr, typename u>
    struct unify<rel<lExpr>, rel<rExpr>, u> : public unify<lExpr, rExpr, u>
    {};

    template<template<typename, typename...> class rel, typename lHExpr, typename lTExpr, typename rHExpr, typename rTExpr, typename u>
    class unify<rel<lHExpr, lTExpr>, rel<rHExpr, rTExpr>, u> :
            public boost::mpl::if_
            <
                unify<lHExpr, rHExpr, u>,
                unify<lTExpr, rTExpr, typename unify<lHExpr, rHExpr, u>::unifiers>,
                boost::mpl::false_
            >::type
    {
        private:
            template<typename, typename>
            struct lazy;

            template<typename unification>
            struct lazy<boost::mpl::true_, unification>
            {
                    typedef typename unification::unifiers type;
            };

            template<typename _>
            struct lazy<boost::mpl::false_, _>
            {
                    typedef boost::mpl::map<> type;
            };

            typedef typename unify<lHExpr, rHExpr, u>::unifiers hUnifiers;
            typedef typename unify::template lazy<typename unify::type, unify<lTExpr, rTExpr, typename unify::hUnifiers > >::type tUnifiers;

        public:
            typedef typename boost::mpl::if_
            <
                unify,
                typename boost::mpl::fold<typename unify::tUnifiers, typename unify::hUnifiers, boost::mpl::insert<boost::mpl::_1, boost::mpl::_2> >::type,
                boost::mpl::map<>
            >::type unifiers;
    };

    //shortcuts
    template<template<typename, typename...> class rel, typename hExpr, typename lTExpr, typename rTExpr, typename u>
    struct unify<rel<hExpr, lTExpr>, rel<hExpr, rTExpr>, u> : public unify<lTExpr, rTExpr, u>
    {};

    template<template<typename, typename...> class rel, typename lHExpr, typename rHExpr, typename tExpr, typename u>
    struct unify<rel<lHExpr, tExpr>, rel<rHExpr, tExpr>, u> : public unify<lHExpr, rHExpr, u>
    {};

    template<template<typename, typename...> class rel, typename hExpr, typename tExpr, typename u>
    struct unify<rel<hExpr, tExpr>, rel<hExpr, tExpr>, u> : public boost::mpl::true_
    {
            typedef u unifiers;
    };
}

#endif
