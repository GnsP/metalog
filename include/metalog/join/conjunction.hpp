/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _METALOG_CONJUNCTION_HPP_
#define _METALOG_CONJUNCTION_HPP_

#include "../types.hpp"

#include "../detail/preprocessor.hpp"

#include <boost/config.hpp>

#include <boost/preprocessor/debug/assert.hpp>
#include <boost/preprocessor/comparison/less_equal.hpp>
#include <boost/preprocessor/logical/and.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/arithmetic/add.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

#include <boost/mpl/identity.hpp>

namespace metalog
{
#define METALOG_DEFINE_JOIN(X, Y) \
    BOOST_PP_ASSERT(BOOST_PP_LESS_EQUAL(0, X)) \
    BOOST_PP_ASSERT(BOOST_PP_LESS_EQUAL(X, METALOG_MAX_VARIADIC_ARGS)) \
    BOOST_PP_ASSERT(BOOST_PP_LESS_EQUAL(0, Y)) \
    BOOST_PP_ASSERT(BOOST_PP_LESS_EQUAL(Y, METALOG_MAX_VARIADIC_ARGS)) \
    template<METALOG_VARIADIC_PARAMS(X, lH) BOOST_PP_COMMA_IF(BOOST_PP_AND(X, Y)) METALOG_VARIADIC_PARAMS(Y, rH)> \
    struct join \
            < \
                conjunction \
                < \
                    METALOG_VARIADIC_ARGS(X, lH) \
                    BOOST_PP_COMMA_IF(BOOST_PP_AND(X, BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, X))) \
                    METALOG_VARIADIC_EMPTY_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, X)) \
                >, \
                conjunction \
                < \
                    METALOG_VARIADIC_ARGS(Y, rH) \
                    BOOST_PP_COMMA_IF(BOOST_PP_AND(Y, BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, Y))) \
                    METALOG_VARIADIC_EMPTY_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, Y)) \
                > \
                METALOG_TRAILING_VARIADIC_EMPTY_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 2)) \
            > : \
        boost::mpl::identity<conjunction<METALOG_VARIADIC_ARGS(X, lH) BOOST_PP_COMMA_IF(BOOST_PP_AND(X, Y)) METALOG_VARIADIC_ARGS(Y, rH)> > \
    {};

#define METALOG_DEFINE_VARIADIC_JOIN(X, Y) \
    BOOST_PP_ASSERT(BOOST_PP_LESS_EQUAL(0, X)) \
    BOOST_PP_ASSERT(BOOST_PP_LESS_EQUAL(X, METALOG_MAX_VARIADIC_ARGS)) \
    BOOST_PP_ASSERT(BOOST_PP_LESS_EQUAL(0, Y)) \
    BOOST_PP_ASSERT(BOOST_PP_LESS_EQUAL(Y, METALOG_MAX_VARIADIC_ARGS)) \
    template \
    < \
            METALOG_LEADING_VARIADIC_PARAMS(X, lH) \
            METALOG_LEADING_VARIADIC_PARAMS(Y, rH) \
            METALOG_VARIADIC_PARAMS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 2), t) \
    > \
    struct join \
            < \
                conjunction \
                < \
                    METALOG_VARIADIC_ARGS(X, lH) \
                    BOOST_PP_COMMA_IF(BOOST_PP_AND(X, BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, X))) \
                    METALOG_VARIADIC_EMPTY_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, X)) \
                >, \
                conjunction \
                < \
                    METALOG_VARIADIC_ARGS(Y, rH) \
                    BOOST_PP_COMMA_IF(BOOST_PP_AND(Y, BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, Y))) \
                    METALOG_VARIADIC_EMPTY_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, Y)) \
                >, \
                METALOG_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 2), t) \
            > : \
        join \
        < \
            conjunction<METALOG_VARIADIC_ARGS(X, lH) BOOST_PP_COMMA_IF(BOOST_PP_AND(X, Y)) METALOG_VARIADIC_ARGS(Y, rH)>, \
            METALOG_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 2), t) \
        > \
    {};

#ifdef BOOST_NO_CXX11_VARIADIC_TEMPLATES

#define METALOG_FORWARD_DEFINE_JOIN(Z, N, DATA) \
    METALOG_DEFINE_JOIN(N, BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, N))

    METALOG_DEFINE_JOIN(0, 0)
    BOOST_PP_REPEAT_FROM_TO(0, BOOST_PP_ADD(METALOG_MAX_VARIADIC_ARGS, 1), METALOG_FORWARD_DEFINE_JOIN, _)

#define METALOG_FORWARD_DEFINE_VARIADIC_JOIN(Z, N, DATA) \
    METALOG_DEFINE_VARIADIC_JOIN(N, BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, N))

    METALOG_DEFINE_VARIADIC_JOIN(0, 0)
    BOOST_PP_REPEAT_FROM_TO(0, BOOST_PP_ADD(METALOG_MAX_VARIADIC_ARGS, 1), METALOG_FORWARD_DEFINE_VARIADIC_JOIN, _)

#else
    METALOG_DEFINE_JOIN(METALOG_MAX_VARIADIC_ARGS, METALOG_MAX_VARIADIC_ARGS)
    METALOG_DEFINE_VARIADIC_JOIN(METALOG_MAX_VARIADIC_ARGS, METALOG_MAX_VARIADIC_ARGS)
#endif
}

#endif
