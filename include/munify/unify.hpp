/*
 * This file is part of munify, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _MUNIFY_UNIFY_HPP_
#define _MUNIFY_UNIFY_HPP_

#include "substitute.hpp"

#include <boost/mpl/bool.hpp>
#include <boost/mpl/arg.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/map.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/type_traits.hpp>

namespace munify
{
    //base: unification of constants
    template<typename lExpr, typename rExpr, typename u = boost::mpl::map<> >
    struct unify : public boost::mpl::bool_<boost::is_same<lExpr, rExpr>::value>
    {
            typedef boost::mpl::map<> unifiers;
    };

    //{lRel(lExpr_1, lExpr_2, ..., lExpr_n-1, lExpr_n) = rRel(rExpr_1, rExpr_2, ..., rExpr_n-1, rExpr_n)} ==
    //    {lRel(lExpr_1, _(lExpr_2, _(..., _(lExpr_n-1, lExpr_n)))) = rRel(rExpr_1, _(rExpr_2, _(..., _(rExpr_n-1, rExpr_n))))}
    template<template<typename, typename...> class lRel, typename lHExpr, typename... lTExpr, template<typename, typename...> class rRel, typename rHExpr, typename... rTExpr, typename u>
    struct unify<lRel<lHExpr, lTExpr...>, rRel<rHExpr, rTExpr...>, u> : public unify<lRel<lHExpr, boost::tuples::tuple<lTExpr...> >, rRel<rHExpr, boost::tuples::tuple<rTExpr...> >, u>
    {};

    //type modifiers forwarding
//    template<typename lExpr, typename rExpr>
//    struct unify<lExpr*, rExpr*, boost::mpl::map<> > : public unify<lExpr, rExpr>
//    {
//            typedef boost::mpl::map<> unifiers;
//    };

    //main recursion
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

    //main recursion shortcuts
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

    //variable binding
    template<int n, typename expr>
    struct unify<boost::mpl::arg<n>, expr, boost::mpl::map<> > : public boost::mpl::true_
    {
            //TODO: occurs check
            typedef boost::mpl::map<boost::mpl::pair<boost::mpl::arg<n>, expr> > unifiers;
    };

    template<int n, typename expr, typename u>
    class unify<boost::mpl::arg<n>, expr, u> : public unify<typename substitute<u, boost::mpl::arg<n> >::type, typename substitute<u, expr>::type >
    {
        private:
            typedef typename unify<typename substitute<u, boost::mpl::arg<n> >::type, typename substitute<u, expr>::type>::unifiers tUnifiers;

        public:
            typedef typename boost::mpl::if_
            <
                unify,
                typename boost::mpl::fold<typename unify::tUnifiers, u, boost::mpl::insert<boost::mpl::_1, boost::mpl::_2> >::type,
                boost::mpl::map<>
            >::type unifiers;
    };

    template<int n, typename expr, typename u>
    struct unify<expr, boost::mpl::arg<n>, u> : public unify<boost::mpl::arg<n>, expr, u>
    {};

    template<int m, int n>
    struct unify<boost::mpl::arg<m>, boost::mpl::arg<n>, boost::mpl::map<> > : public boost::mpl::true_
    {
            typedef boost::mpl::map<boost::mpl::pair<boost::mpl::arg<m>, boost::mpl::arg<n> > > unifiers;
    };

    template<int m, int n, typename u>
    struct unify<boost::mpl::arg<m>, boost::mpl::arg<n>, u> : public unify<typename substitute<u, boost::mpl::arg<m> >::type, typename substitute<u, boost::mpl::arg<n> >::type>
    {
        private:
            typedef typename unify<typename substitute<u, boost::mpl::arg<m> >::type, typename substitute<u, boost::mpl::arg<n> >::type>::unifiers tUnifiers;

        public:
            typedef typename boost::mpl::if_
            <
                unify,
                typename boost::mpl::fold<typename unify::tUnifiers, u, boost::mpl::insert<boost::mpl::_1, boost::mpl::_2> >::type,
                boost::mpl::map<>
            >::type unifiers;
    };

    //variable binding shortcuts
    template<int n, typename u>
    struct unify<boost::mpl::arg<n>, boost::mpl::arg<n>, u> : public boost::mpl::true_
    {
            typedef u unifiers;
    };

    //variable binding ambiguity avoidance
    template<int n>
    struct unify<boost::mpl::arg<n>, boost::mpl::arg<n>, boost::mpl::map<> > : public boost::mpl::true_
    {
            typedef boost::mpl::map<> unifiers;
    };
}

#endif
