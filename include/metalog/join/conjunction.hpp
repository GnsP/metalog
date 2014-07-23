/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _METALOG_CONJUNCTION_HPP_
#define _METALOG_CONJUNCTION_HPP_

#include "../types.hpp"

#include "../detail/empty.hpp"
#include "../detail/preprocessor.hpp"

#include <boost/config.hpp>

#include <boost/preprocessor/debug/assert.hpp>
#include <boost/preprocessor/comparison/less_equal.hpp>
#include <boost/preprocessor/logical/and.hpp>
#include <boost/preprocessor/logical/or.hpp>
#include <boost/preprocessor/if.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/arithmetic/add.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

#include <boost/mpl/identity.hpp>

namespace metalog
{

    namespace detail
    {
        template<METALOG_VARIADIC_PARAMS_DECLARATION(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1), _)>
        struct join_conjunction_impl;
    }

#define METALOG_DEFINE_JOIN_CONJUNCTION_IMPL(X, Y, Z) \
    BOOST_PP_ASSERT(BOOST_PP_LESS_EQUAL(0, X)) \
    BOOST_PP_ASSERT(BOOST_PP_LESS_EQUAL(X, METALOG_MAX_VARIADIC_ARGS)) \
    BOOST_PP_ASSERT(BOOST_PP_LESS_EQUAL(0, Y)) \
    BOOST_PP_ASSERT(BOOST_PP_LESS_EQUAL(Y, METALOG_MAX_VARIADIC_ARGS)) \
    BOOST_PP_ASSERT(BOOST_PP_LESS_EQUAL(2, Z)) \
    BOOST_PP_ASSERT(BOOST_PP_LESS_EQUAL(Z, METALOG_MAX_VARIADIC_ARGS)) \
namespace detail \
{ \
    template \
    < \
        METALOG_VARIADIC_PARAMS(Y, rH) \
        BOOST_PP_COMMA_IF(BOOST_PP_AND(Y, BOOST_PP_SUB(Z, 2))) \
        METALOG_VARIADIC_PARAMS(BOOST_PP_SUB(Z, 2), t) \
    > \
    struct join_conjunction_impl \
    < \
        conjunction \
        < \
            METALOG_VARIADIC_ARGS(Y, rH) \
            BOOST_PP_COMMA_IF(BOOST_PP_AND(Y, BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, Y))) \
            METALOG_VARIADIC_EMPTY_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, Y)) \
        > \
        METALOG_TRAILING_VARIADIC_ARGS(BOOST_PP_SUB(Z, 2), t) \
        METALOG_TRAILING_VARIADIC_EMPTY_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, Z)) \
    > \
    { \
        template<typename, typename = _> \
        struct apply; \
        template \
        < \
            METALOG_LEADING_VARIADIC_PARAMS(X, lH) \
            typename _ \
        > \
        struct apply \
        < \
            conjunction \
            < \
                METALOG_VARIADIC_ARGS(X, lH) \
                BOOST_PP_COMMA_IF(BOOST_PP_AND(X, BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, X))) \
                METALOG_VARIADIC_EMPTY_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, X)) \
            >, \
            _ \
        > : \
            BOOST_PP_IF(BOOST_PP_SUB(Z, 2), join, boost::mpl::identity)\
            < \
                conjunction<METALOG_VARIADIC_ARGS(X, lH) BOOST_PP_COMMA_IF(BOOST_PP_AND(X, Y)) METALOG_VARIADIC_ARGS(Y, rH)> \
                METALOG_TRAILING_VARIADIC_ARGS(BOOST_PP_SUB(Z, 2), t) \
            > \
        {};\
    }; \
}

#ifdef BOOST_NO_CXX11_VARIADIC_TEMPLATES

#define METALOG_FORWARD_FOR_EACH_JOIN_CONJUNCTION_DEFINITION(Z, X, _) \
    METALOG_DEFINE_JOIN_CONJUNCTION_IMPL(X, BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, X), 2) \
    METALOG_DEFINE_JOIN_CONJUNCTION_IMPL(X, BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, X), METALOG_MAX_VARIADIC_ARGS)

    BOOST_PP_REPEAT_FROM_TO(0, BOOST_PP_ADD(METALOG_MAX_VARIADIC_ARGS, 1), METALOG_FORWARD_FOR_EACH_JOIN_CONJUNCTION_DEFINITION, _)

#else
    METALOG_DEFINE_JOIN_CONJUNCTION_IMPL(METALOG_MAX_VARIADIC_ARGS, METALOG_MAX_VARIADIC_ARGS, 2)
    METALOG_DEFINE_JOIN_CONJUNCTION_IMPL(METALOG_MAX_VARIADIC_ARGS, METALOG_MAX_VARIADIC_ARGS, METALOG_MAX_VARIADIC_ARGS)
#endif

#define METALOG_DEFINE_JOIN_CONJUNCTION(N) \
    BOOST_PP_ASSERT(BOOST_PP_LESS_EQUAL(0, N)) \
    BOOST_PP_ASSERT(BOOST_PP_LESS_EQUAL(N, METALOG_MAX_VARIADIC_ARGS)) \
    template \
    < \
        METALOG_VARIADIC_PARAMS(METALOG_MAX_VARIADIC_ARGS, lArgs), \
        METALOG_VARIADIC_PARAMS(METALOG_MAX_VARIADIC_ARGS, rArgs) \
        METALOG_TRAILING_VARIADIC_PARAMS(BOOST_PP_SUB(N, 2), t) \
    > \
    struct join \
    < \
        conjunction<METALOG_VARIADIC_ARGS(METALOG_MAX_VARIADIC_ARGS, lArgs)>, \
        conjunction<METALOG_VARIADIC_ARGS(METALOG_MAX_VARIADIC_ARGS, rArgs)> \
        METALOG_TRAILING_VARIADIC_ARGS(BOOST_PP_SUB(N, 2), t) \
        METALOG_TRAILING_VARIADIC_EMPTY_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, N)) \
    > : \
        detail::join_conjunction_impl \
        < \
            conjunction<METALOG_VARIADIC_ARGS(METALOG_MAX_VARIADIC_ARGS, rArgs)> \
            METALOG_TRAILING_VARIADIC_ARGS(BOOST_PP_SUB(N, 2), t) \
        >::template apply<conjunction<METALOG_VARIADIC_ARGS(METALOG_MAX_VARIADIC_ARGS, lArgs)> > \
    {};

    METALOG_DEFINE_JOIN_CONJUNCTION(2)
    METALOG_DEFINE_JOIN_CONJUNCTION(METALOG_MAX_VARIADIC_ARGS)
}

#endif
