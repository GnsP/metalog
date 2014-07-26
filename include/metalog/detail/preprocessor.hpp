/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#include <boost/config.hpp>
#include <boost/preprocessor/comparison/less_equal.hpp>
#include <boost/preprocessor/comma_if.hpp>

#ifndef METALOG_MAX_VARIADIC_ARGS
#define METALOG_MAX_VARIADIC_ARGS 20
#endif

#if defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) || defined(METALOG_DISABLE_VARIADIC_TEMPLATES)

#include "empty.hpp"

#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/seq/elem.hpp>

#undef METALOG_FORWARD_MACRO_FOR_EACH_VARIADIC_IDENTIFIER
#define METALOG_FORWARD_MACRO_FOR_EACH_VARIADIC_IDENTIFIER(Z, N, DATA) \
    BOOST_PP_SEQ_ELEM(1, DATA)(BOOST_PP_CAT(BOOST_PP_SEQ_ELEM(0, DATA), N))

#undef METALOG_FOR_EACH_VARIADIC_IDENTIFIER
#define METALOG_FOR_EACH_VARIADIC_IDENTIFIER(N, PREFIX, MACRO) \
    BOOST_PP_ENUM(N, METALOG_FORWARD_MACRO_FOR_EACH_VARIADIC_IDENTIFIER, (PREFIX)(MACRO))

#undef METALOG_VARIADIC_EMPTY_ARG
#define METALOG_VARIADIC_EMPTY_ARG(ARG) \
    detail::_

#undef METALOG_VARIADIC_EMPTY_ARGS
#define METALOG_VARIADIC_EMPTY_ARGS(N) \
    METALOG_FOR_EACH_VARIADIC_IDENTIFIER(N, _, METALOG_VARIADIC_EMPTY_ARG)

#undef METALOG_TRAILING_VARIADIC_EMPTY_ARGS
#define METALOG_TRAILING_VARIADIC_EMPTY_ARGS(N) \
    BOOST_PP_COMMA_IF(N) METALOG_VARIADIC_EMPTY_ARGS(N)

#undef METALOG_VARIADIC_PARAM_DECLARATION
#define METALOG_VARIADIC_PARAM_DECLARATION(PARAM) \
    typename PARAM = METALOG_VARIADIC_EMPTY_ARG(_)

#undef METALOG_VARIADIC_PARAMS_DECLARATION
#define METALOG_VARIADIC_PARAMS_DECLARATION(N, PREFIX) \
    METALOG_FOR_EACH_VARIADIC_IDENTIFIER(N, PREFIX, METALOG_VARIADIC_PARAM_DECLARATION)

#undef METALOG_VARIADIC_PARAM
#define METALOG_VARIADIC_PARAM(PARAM) \
    typename PARAM

#undef METALOG_VARIADIC_PARAMS
#define METALOG_VARIADIC_PARAMS(N, PREFIX) \
    METALOG_FOR_EACH_VARIADIC_IDENTIFIER(N, PREFIX, METALOG_VARIADIC_PARAM)

#undef METALOG_VARIADIC_ARG
#define METALOG_VARIADIC_ARG(ARG) \
    ARG

#undef METALOG_VARIADIC_ARGS
#define METALOG_VARIADIC_ARGS(N, PREFIX) \
    METALOG_FOR_EACH_VARIADIC_IDENTIFIER(N, PREFIX, METALOG_VARIADIC_ARG)

#undef METALOG_FOR_EACH_VARIADIC_ARG
#define METALOG_FOR_EACH_VARIADIC_ARG(N, PREFIX, MACRO) \
    METALOG_FOR_EACH_VARIADIC_IDENTIFIER(N, PREFIX, MACRO)

#else

#include <boost/preprocessor/if.hpp>
#include <boost/preprocessor/expr_if.hpp>
#include <boost/preprocessor/expand.hpp>
#include <boost/preprocessor/identity.hpp>
#include <boost/preprocessor/tuple/eat.hpp>

#undef METALOG_VARIADIC_EMPTY_ARGS
#define METALOG_VARIADIC_EMPTY_ARGS(N)

#undef METALOG_TRAILING_VARIADIC_EMPTY_ARGS
#define METALOG_TRAILING_VARIADIC_EMPTY_ARGS(N)

#undef METALOG_VARIADIC_PARAMS_DECLARATION
#define METALOG_VARIADIC_PARAMS_DECLARATION(N, PREFIX) \
    BOOST_PP_EXPR_IF(N, typename... PREFIX)

#undef METALOG_VARIADIC_PARAMS
#define METALOG_VARIADIC_PARAMS(N, PREFIX) \
    BOOST_PP_EXPR_IF(N, typename... PREFIX)

#undef METALOG_VARIADIC_ARGS
#define METALOG_VARIADIC_ARGS(N, PREFIX) \
    BOOST_PP_EXPR_IF(N, PREFIX...)

#undef METALOG_FOR_EACH_VARIADIC_ARG
#define METALOG_FOR_EACH_VARIADIC_ARG(N, PREFIX, MACRO) \
    BOOST_PP_IF(N, BOOST_PP_EXPAND, BOOST_PP_TUPLE_EAT(1))(MACRO BOOST_PP_IDENTITY((PREFIX))()...)

#endif

#define METALOG_LEADING_VARIADIC_PARAMS(N, PREFIX) \
    METALOG_VARIADIC_PARAMS(N, PREFIX) BOOST_PP_COMMA_IF(N)

#define METALOG_LEADING_VARIADIC_ARGS(N, PREFIX) \
    METALOG_VARIADIC_ARGS(N, PREFIX) BOOST_PP_COMMA_IF(N)

#define METALOG_TRAILING_VARIADIC_PARAMS(N, PREFIX) \
    BOOST_PP_COMMA_IF(N) METALOG_VARIADIC_PARAMS(N, PREFIX)

#define METALOG_TRAILING_VARIADIC_ARGS(N, PREFIX) \
    BOOST_PP_COMMA_IF(N) METALOG_VARIADIC_ARGS(N, PREFIX)

#define METALOG_FOR_EACH_TRAILING_VARIADIC_ARG(N, PREFIX, MACRO) \
    BOOST_PP_COMMA_IF(N) METALOG_FOR_EACH_VARIADIC_ARG(N, PREFIX, MACRO)
