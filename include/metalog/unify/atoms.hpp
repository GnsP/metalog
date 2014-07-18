/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _METALOG_UNIFY_ATOMS_HPP_
#define _METALOG_UNIFY_ATOMS_HPP_

#include "../minimize.hpp"

#include "../detail/lazy.hpp"
#include "../detail/preprocessor.hpp"

#include <boost/preprocessor/arithmetic/sub.hpp>

#include <boost/mpl/bool.hpp>
#include <boost/mpl/map.hpp>
#include <boost/mpl/apply_wrap.hpp>

namespace metalog
{
    template<typename lExpr, typename rExpr, typename u>
    struct unify<lExpr, rExpr, u METALOG_TRAILING_VARIADIC_EMPTY_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1))> :
            unify<atom<lExpr>, atom<rExpr>, u>
    {};

    template<typename lExpr, typename rExpr, typename u>
    struct unify<atom<lExpr>, atom<rExpr>, u METALOG_TRAILING_VARIADIC_EMPTY_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1))> :
            boost::mpl::false_
    {
        typedef boost::mpl::map<> unifiers;
    };

    template<typename expr, typename u>
    struct unify<atom<expr>, atom<expr>, u METALOG_TRAILING_VARIADIC_EMPTY_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1))> :
            boost::mpl::true_
    {
        typedef typename minimize<u>::type unifiers;
    };

    template<typename lExpr, typename rExpr, typename u>
    struct unify<atom<detail::lazy<lExpr> >, atom<rExpr>, u METALOG_TRAILING_VARIADIC_EMPTY_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1))> :
            unify<atom<typename boost::mpl::apply_wrap0<lExpr>::type>, atom<rExpr>, u>
    {};

    template<typename lExpr, typename rExpr, typename u>
    struct unify<atom<lExpr>, atom<detail::lazy<rExpr> >, u METALOG_TRAILING_VARIADIC_EMPTY_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1))> :
            unify<atom<lExpr>, atom<typename boost::mpl::apply_wrap0<rExpr>::type>, u>
    {};

    template<typename lExpr, typename rExpr, typename u>
    struct unify<atom<detail::lazy<lExpr> >, atom<detail::lazy<rExpr> >, u METALOG_TRAILING_VARIADIC_EMPTY_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1))> :
            unify<atom<typename boost::mpl::apply_wrap0<lExpr>::type>, atom<typename boost::mpl::apply_wrap0<rExpr>::type>, u>
    {};
}

#endif
