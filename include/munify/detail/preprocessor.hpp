/*
 * This file is part of munify, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _MUNIFY_DETAIL_PREPROCESSOR_HPP_
#define _MUNIFY_DETAIL_PREPROCESSOR_HPP_

#include <boost/config.hpp>

#ifdef BOOST_NO_CXX11_VARIADIC_TEMPLATES

#include "empty.hpp"

#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/comma_if.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>

#define MUNIFY_MAX_VARIADIC_ARGS 10

#define MUNIFY_VARIADIC_PARAMS_DECL(N) \
    BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(BOOST_PP_SUB(MUNIFY_MAX_VARIADIC_ARGS, N), typename _, munify::detail::empty)

#define MUNIFY_VARIADIC_PARAMS(N, PARAM) \
    BOOST_PP_ENUM_PARAMS(BOOST_PP_SUB(MUNIFY_MAX_VARIADIC_ARGS, N), typename PARAM)

#define MUNIFY_VARIADIC_ARGS(N, ARG) \
    BOOST_PP_ENUM_PARAMS(BOOST_PP_SUB(MUNIFY_MAX_VARIADIC_ARGS, N), ARG)

#define MUNIFY_EMPTY_VARIADIC_ARG(Z, N, ARG) \
    ARG

#define MUNIFY_EMPTY_VARIADIC_ARGS(N) \
    BOOST_PP_ENUM(BOOST_PP_SUB(MUNIFY_MAX_VARIADIC_ARGS, N), MUNIFY_EMPTY_VARIADIC_ARG, munify::detail::empty)

#else

#define MUNIFY_VARIADIC_PARAMS_DECL(N) \
    typename...

#define MUNIFY_VARIADIC_PARAMS(N, PARAM) \
    typename... PARAM

#define MUNIFY_VARIADIC_ARGS(N, ARG) \
    ARG...

#endif

#endif
