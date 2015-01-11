/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#include <boost/config.hpp>

#ifdef BOOST_NO_CXX11_VARIADIC_TEMPLATES

#   include "args.hpp"

#   undef METALOG_FOR_EACH_VARIADIC_ARG
#   define METALOG_FOR_EACH_VARIADIC_ARG(N, PREFIX, MACRO) \
        METALOG_FOR_EACH_ARG(N, PREFIX, MACRO)

#   undef METALOG_VARIADIC_ARGS
#   define METALOG_VARIADIC_ARGS(N, PREFIX) \
        METALOG_ARGS(N, PREFIX)

#   undef METALOG_VARIADIC_PARAMS
#   define METALOG_VARIADIC_PARAMS(N, PREFIX) \
        METALOG_PARAMS(N, PREFIX)

#   undef METALOG_VARIADIC_OPTIONAL_PARAMS
#   define METALOG_VARIADIC_OPTIONAL_PARAMS(N, PREFIX) \
        METALOG_OPTIONAL_PARAMS(N, PREFIX)

#else

#   include <boost/preprocessor/if.hpp>
#   include <boost/preprocessor/expr_if.hpp>
#   include <boost/preprocessor/expand.hpp>
#   include <boost/preprocessor/identity.hpp>
#   include <boost/preprocessor/tuple/eat.hpp>

#   undef METALOG_FOR_EACH_VARIADIC_ARG
#   define METALOG_FOR_EACH_VARIADIC_ARG(N, PREFIX, MACRO) \
        BOOST_PP_IF(N, BOOST_PP_EXPAND, BOOST_PP_TUPLE_EAT(1))(MACRO BOOST_PP_IDENTITY((PREFIX))()...)

#   undef METALOG_VARIADIC_ARGS
#   define METALOG_VARIADIC_ARGS(N, PREFIX) \
        BOOST_PP_EXPR_IF(N, PREFIX...)

#   undef METALOG_VARIADIC_PARAMS
#   define METALOG_VARIADIC_PARAMS(N, PREFIX) \
        BOOST_PP_EXPR_IF(N, typename... PREFIX)

#   undef METALOG_VARIADIC_OPTIONAL_PARAMS
#   define METALOG_VARIADIC_OPTIONAL_PARAMS(N, PREFIX) \
        BOOST_PP_EXPR_IF(N, typename... PREFIX)

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
