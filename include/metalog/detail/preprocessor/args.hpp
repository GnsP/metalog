/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _METALOG_DETAIL_PREPROCESSOR_ARGS_HPP_
#define _METALOG_DETAIL_PREPROCESSOR_ARGS_HPP_

#include "../empty.hpp"

#include <boost/preprocessor/comma_if.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/seq/elem.hpp>

#define METALOG_FORWARD_MACRO_FOR_EACH_ARG(Z, N, DATA) \
    BOOST_PP_SEQ_ELEM(1, DATA)(BOOST_PP_SEQ_ELEM(2, DATA), BOOST_PP_CAT(BOOST_PP_SEQ_ELEM(0, DATA), N))

#define METALOG_FOR_EACH_ARG(N, PREFIX, MACRO, DATA) \
    BOOST_PP_ENUM(N, METALOG_FORWARD_MACRO_FOR_EACH_ARG, (PREFIX)(MACRO)(DATA))

#define METALOG_CALL_FOR_ARG(FUNC, ARG) \
    typename FUNC<ARG>::type

#define METALOG_CALL_FOR_EACH_ARG(N, PREFIX, FUNC) \
    METALOG_FOR_EACH_ARG(N, PREFIX, METALOG_CALL_FOR_ARG, FUNC)

#define METALOG_WRAP_ARG(WRAP, ARG) \
    WRAP<ARG>

#define METALOG_WRAP_EACH_ARG(N, PREFIX, WRAP) \
    METALOG_FOR_EACH_ARG(N, PREFIX, METALOG_WRAP_ARG, WRAP)

#define METALOG_ARGS(N, PREFIX) \
    BOOST_PP_ENUM_PARAMS(N, PREFIX)

#define METALOG_PARAMS(N, PREFIX) \
    BOOST_PP_ENUM_PARAMS(N, typename PREFIX)

#define METALOG_OPTIONAL_PARAMS(N, PREFIX) \
    BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(N, typename PREFIX, detail::_)

#define METALOG_FOR_EACH_LEADING_ARG(N, PREFIX, MACRO) \
    METALOG_FOR_EACH_ARG(N, PREFIX, MACRO) BOOST_PP_COMMA_IF(N)

#define METALOG_FOR_EACH_TRAILING_ARG(N, PREFIX, MACRO) \
    BOOST_PP_COMMA_IF(N) METALOG_FOR_EACH_ARG(N, PREFIX, MACRO)

#define METALOG_LEADING_ARGS(N, PREFIX) \
    METALOG_ARGS(N, PREFIX) BOOST_PP_COMMA_IF(N)

#define METALOG_TRAILING_ARGS(N, PREFIX) \
    BOOST_PP_COMMA_IF(N) METALOG_ARGS(N, PREFIX)

#define METALOG_LEADING_PARAMS(N, PREFIX) \
    METALOG_PARAMS(N, PREFIX) BOOST_PP_COMMA_IF(N)

#define METALOG_TRAILING_PARAMS(N, PREFIX) \
    BOOST_PP_COMMA_IF(N) METALOG_PARAMS(N, PREFIX)

#endif
