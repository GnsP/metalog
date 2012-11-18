/*
 * This file is part of munify, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#include <boost/mpl/bool.hpp>
#include <boost/mpl/arg.hpp>
#include <boost/mpl/placeholders.hpp>

namespace munify
{
    template<typename lexpr, typename rexpr>
    struct unify : boost::mpl::false_
    {};

    template<typename atom>
    struct unify<atom, atom> : boost::mpl::true_
    {
    };

    template<int n, typename expr>
    struct unify<boost::mpl::arg<n>, expr> : boost::mpl::true_
    {
            //TODO: occurs check
    };

    //required to avoid ambiguity
    template<int n>
    struct unify<boost::mpl::arg<n>, boost::mpl::arg<n> > : boost::mpl::true_
    {
    };

    template<template<typename...> class lexpr, typename... largs, template<typename...> class rexpr, typename... rargs>
    struct unify<lexpr<largs...>, rexpr<rargs...> >
    {

    };

    //required to avoid ambiguity
    template<template<typename...> class expr, typename... args>
    struct unify<expr<args...>, expr<args...> > : boost::mpl::true_
    {

    };
}
