/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _METALOG_SUBSTITUTE_HPP_
#define _METALOG_SUBSTITUTE_HPP_

#include "atom.hpp"
#include "var.hpp"

#include "detail/lazy.hpp"
#include "detail/preprocessor.hpp"

#include <boost/config.hpp>

#include <boost/preprocessor/debug/assert.hpp>
#include <boost/preprocessor/comparison/less_equal.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

#include <boost/mpl/bind.hpp>
#include <boost/mpl/quote.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/has_key.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>

#define METALOG_FORWARD_SUBSTITUTION(ARG) \
    typename apply<ARG>::type

#define METALOG_DEFINE_TERM_SUBSTITUTION(N) \
    BOOST_PP_ASSERT(BOOST_PP_LESS_EQUAL(1, N)) \
    template<typename u> \
    template<template<METALOG_VARIADIC_PARAMS(N, _)> class term, typename hExpr METALOG_TRAILING_VARIADIC_PARAMS(BOOST_PP_SUB(N, 1), tExpr)> \
    struct substitute<u>:: \
        apply<term<hExpr METALOG_TRAILING_VARIADIC_ARGS(BOOST_PP_SUB(N, 1), tExpr)> > : \
                boost::mpl::identity \
                < \
                    term \
                    < \
                        METALOG_FORWARD_SUBSTITUTION(hExpr) \
                        METALOG_FOR_EACH_TRAILING_VARIADIC_ARG(BOOST_PP_SUB(N, 1), tExpr, METALOG_FORWARD_SUBSTITUTION) \
                    > \
                > \
    {};

#define METALOG_FORWARD_DEFINE_TERM_SUBSTITUTION(Z, N, DATA) \
    METALOG_DEFINE_TERM_SUBSTITUTION(N)

namespace metalog
{
    template<typename u>
    struct substitute
    {
        template<typename expr>
        struct apply:
                boost::mpl::identity<expr>
        {};
    };

    template<typename u>
    template<typename expr>
    struct substitute<u>::apply<detail::lazy<expr> > :
           apply<typename detail::lazy<expr>::type>
    {};

    template<typename u>
    template<typename expr>
    struct substitute<u>::apply<atom<expr> > :
            boost::mpl::identity<atom<expr> >
    {};

    template<typename u>
    template<typename n>
    struct substitute<u>::apply<var<n> > :
            boost::mpl::eval_if
            <
                boost::mpl::has_key<unifiers<u>, var<n> >,
                apply<detail::lazy<boost::mpl::bind<boost::mpl::quote2<boost::mpl::at>, unifiers<u>, var<n> > > >,
                boost::mpl::identity<var<n> >
            >
    {};

#ifdef BOOST_NO_CXX11_VARIADIC_TEMPLATES
    BOOST_PP_REPEAT_FROM_TO(1, METALOG_MAX_ARGS, METALOG_FORWARD_DEFINE_TERM_SUBSTITUTION, _)
#endif

    METALOG_DEFINE_TERM_SUBSTITUTION(METALOG_MAX_ARGS)
}

#undef METALOG_FORWARD_SUBSTITUTION
#undef METALOG_DEFINE_TERM_SUBSTITUTION
#undef METALOG_FORWARD_DEFINE_TERM_SUBSTITUTION

#endif
