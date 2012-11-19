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
#include <boost/mpl/insert.hpp>

namespace munify
{

    template<typename lExpr, typename rExpr, typename unifiers = boost::mpl::map<> >
    struct unify : unify<typename substitute<unifiers, lExpr>::type, typename substitute<unifiers, rExpr>::type>
    {};

    template<typename lExpr, typename rExpr>
    struct unify<lExpr, rExpr, boost::mpl::map<> > : boost::mpl::false_
    {
            typedef boost::mpl::map<> unifiers;
    };

    template<typename atom>
    struct unify<atom, atom, boost::mpl::map<> > : boost::mpl::true_
    {
            typedef boost::mpl::map<> unifiers;
    };

    template<int n, typename expr>
    struct unify<boost::mpl::arg<n>, expr, boost::mpl::map<> > : boost::mpl::true_
    {
            //TODO: occurs check
            typedef boost::mpl::map<boost::mpl::pair<boost::mpl::arg<n>, expr> > unifiers;
    };

    template<int n, typename expr>
    struct unify<expr, boost::mpl::arg<n>, boost::mpl::map<> > : unify<boost::mpl::arg<n>, expr>
    {};

    template<int m, int n>
    struct unify<boost::mpl::arg<m>, boost::mpl::arg<n>, boost::mpl::map<> > : boost::mpl::true_
    {
            typedef boost::mpl::map<boost::mpl::pair<boost::mpl::arg<m>, boost::mpl::arg<n> > > unifiers;
    };

    template<int n>
    struct unify<boost::mpl::arg<n>, boost::mpl::arg<n>, boost::mpl::map<> > : boost::mpl::true_
    {
            typedef boost::mpl::map<> unifiers;
    };

//    template<template<typename...> class lRel, typename... lArgs, template<typename...> class rRel, typename... rArgs>
//    struct unify<lRel<lArgs...>, rRel<rArgs...>, boost::mpl::map<> >
//    {


//    };

    template<template<typename...> class rel, typename... args>
    struct unify<rel<args...>, rel<args...>, boost::mpl::map<> > : boost::mpl::true_
    {
            typedef boost::mpl::map<> unifiers;
    };

}

#endif
