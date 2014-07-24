/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _METALOG_SUBSTITUTE_HPP_
#define _METALOG_SUBSTITUTE_HPP_

#include "types.hpp"

#include "detail/preprocessor.hpp"

#include <boost/config.hpp>
#include <boost/type_traits.hpp>

#include <boost/preprocessor/debug/assert.hpp>
#include <boost/preprocessor/comparison/less_equal.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

#include <boost/mpl/if.hpp>
#include <boost/mpl/apply_wrap.hpp>


namespace metalog
{
    template<typename unifiers>
    struct substitute
    {
        template<typename expr>
        struct apply:
                boost::mpl::identity<expr>
        {};
    };

    template<typename unifiers>
    template<typename expr>
    struct substitute<unifiers>::apply<atom<expr> > :
            boost::mpl::identity<atom<expr> >
    {};

    template<typename unifiers>
    template<typename n>
    struct substitute<unifiers>::apply<var<n> > :
        boost::mpl::if_
        <
            boost::is_same<var<n>, typename lookup<unifiers, var<n> >::type>,
            lookup<unifiers, var<n> >,
            boost::mpl::apply_wrap1<substitute<unifiers>, typename lookup<unifiers, var<n> >::type>
        >::type
    {};

#define METALOG_FORWARD_SUBSTITUTION_TO_ARG(ARG) \
    typename boost::mpl::apply_wrap1<substitute<unifiers>, ARG>::type

#define METALOG_DEFINE_TERM_SUBSTITUTION(N) \
    BOOST_PP_ASSERT(BOOST_PP_LESS_EQUAL(1, N)) \
    template<typename unifiers> \
    template<template<METALOG_VARIADIC_PARAMS(N, _)> class term, typename hExpr METALOG_TRAILING_VARIADIC_PARAMS(BOOST_PP_SUB(N, 1), tExpr)> \
    struct substitute<unifiers>::apply<term<hExpr METALOG_TRAILING_VARIADIC_ARGS(BOOST_PP_SUB(N, 1), tExpr)> > : \
            boost::mpl::identity \
            < \
                term<METALOG_FORWARD_SUBSTITUTION_TO_ARG(hExpr) METALOG_FOR_EACH_TRAILING_VARIADIC_ARG(BOOST_PP_SUB(N, 1), tExpr, METALOG_FORWARD_SUBSTITUTION_TO_ARG)> \
            > \
    {};

#ifdef BOOST_NO_CXX11_VARIADIC_TEMPLATES

#define METALOG_FORWARD_DEFINE_TERM_SUBSTITUTION(Z, N, DATA) \
    METALOG_DEFINE_TERM_SUBSTITUTION(N)

    BOOST_PP_REPEAT_FROM_TO(1, METALOG_MAX_VARIADIC_ARGS, METALOG_FORWARD_DEFINE_TERM_SUBSTITUTION, _)
#endif

METALOG_DEFINE_TERM_SUBSTITUTION(METALOG_MAX_VARIADIC_ARGS)

}

#endif
