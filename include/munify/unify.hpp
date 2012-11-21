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
#include <boost/tuple/tuple.hpp>
#include <boost/mpl/joint_view.hpp>
#include <boost/type_traits.hpp>

namespace munify
{
    //base: unification of constants
    template<typename lExpr, typename rExpr, typename u = boost::mpl::map<> >
    struct unify : boost::mpl::bool_<boost::is_same<lExpr, rExpr>::value>
    {
            typedef boost::mpl::map<> unifiers;
    };

    //{lRel(lExpr_1, lExpr_2, ..., lExpr_n-1, lExpr_n) = rRel(rExpr_1, rExpr_2, ..., rExpr_n-1, rExpr_n)} ==
    //    {lRel(lExpr_1, _(lExpr_2, _(..., _(lExpr_n-1, lExpr_n)))) = rRel(rExpr_1, _(rExpr_2, _(..., _(rExpr_n-1, rExpr_n))))}
    template<template<typename, typename...> class lRel, typename lH, typename... lT, template<typename, typename...> class rRel, typename rH, typename... rT, typename u>
    struct unify<lRel<lH, lT...>, rRel<rH, rT...>, u> : unify<lRel<lH, boost::tuples::tuple<lT...> >, rRel<rH, boost::tuples::tuple<rT...> >, u>
    {};

    //type modifiers forwarding
//    template<typename lExpr, typename rExpr>
//    struct unify<lExpr*, rExpr*, boost::mpl::map<> > : unify<lExpr, rExpr>
//    {
//            typedef boost::mpl::map<> unifiers;
//    };

    //main recursion
    template<template<typename, typename...> class rel, typename lH, typename lT, typename rH, typename rT, typename u>
    class unify<rel<lH, lT>, rel<rH, rT>, u> :
            public boost::mpl::if_
            <
                unify<lH, rH, u>,
                unify<lT, rT, typename unify<lH, rH, u>::unifiers>,
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

        public:
            typedef typename boost::mpl::joint_view
            <
                typename unify::template lazy<typename unify::type, unify<lH, rH, u> >::type,
                typename unify::template lazy<typename unify::type, unify<lT, rT, typename unify<lH, rH, u>::unifiers > >::type
            > unifiers;
    };

    //main recursion shortcuts
    template<template<typename, typename...> class rel, typename h, typename lT, typename rT, typename u>
    struct unify<rel<h, lT>, rel<h, rT>, u> : unify<lT, rT, u>
    {};

    template<template<typename, typename...> class rel, typename lH, typename rH, typename t, typename u>
    struct unify<rel<lH, t>, rel<rH, t>, u> : unify<lH, rH, u>
    {};

    template<template<typename, typename...> class rel, typename h, typename t, typename u>
    struct unify<rel<h, t>, rel<h, t>, u> : boost::mpl::true_
    {
            typedef u unifiers;
    };

    //variable binding
    template<int n, typename expr>
    struct unify<boost::mpl::arg<n>, expr, boost::mpl::map<> > : boost::mpl::true_
    {
            //TODO: occurs check
            typedef boost::mpl::map<boost::mpl::pair<boost::mpl::arg<n>, expr> > unifiers;
    };

    template<int n, typename expr, typename u>
    struct unify<boost::mpl::arg<n>, expr, u> : unify<typename substitute<u, boost::mpl::arg<n> >::type, typename substitute<u, expr>::type >
    {
            typedef boost::mpl::if_
            <
                typename unify::type,
                typename boost::mpl::joint_view
                <
                    u,
                    typename unify<typename substitute<u, boost::mpl::arg<n> >::type, typename substitute<u, expr>::type>::unifiers
                >,
                boost::mpl::map<>
            > unifiers;
    };

    template<int n, typename expr, typename u>
    struct unify<expr, boost::mpl::arg<n>, u> : unify<boost::mpl::arg<n>, expr, u>
    {};

    template<int m, int n>
    struct unify<boost::mpl::arg<m>, boost::mpl::arg<n>, boost::mpl::map<> > : boost::mpl::true_
    {
            typedef boost::mpl::map<boost::mpl::pair<boost::mpl::arg<m>, boost::mpl::arg<n> > > unifiers;
    };

    template<int m, int n, typename u>
    struct unify<boost::mpl::arg<m>, boost::mpl::arg<n>, u> : unify<typename substitute<u, boost::mpl::arg<m> >::type, typename substitute<u, boost::mpl::arg<n> >::type>
    {
            typedef boost::mpl::if_
            <
                typename unify::type,
                typename boost::mpl::joint_view
                <
                    u,
                    typename unify<typename substitute<u, boost::mpl::arg<m> >::type, typename substitute<u, boost::mpl::arg<n> >::type>::unifiers
                >,
                boost::mpl::map<>
            > unifiers;
    };

    //variable binding shortcuts
    template<int n, typename u>
    struct unify<boost::mpl::arg<n>, boost::mpl::arg<n>, u> : boost::mpl::true_
    {
            typedef u unifiers;
    };

    //variable binding ambiguity avoidance
    template<int n>
    struct unify<boost::mpl::arg<n>, boost::mpl::arg<n>, boost::mpl::map<> > : boost::mpl::true_
    {
            typedef boost::mpl::map<> unifiers;
    };
}

#endif
