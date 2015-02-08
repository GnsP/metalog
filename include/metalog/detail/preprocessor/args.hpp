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
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/seq/elem.hpp>

#define METALOG_FORWARD_MACRO_FOR_EACH_ARG(Z, N, DATA) \
    BOOST_PP_SEQ_ELEM(1, DATA)(BOOST_PP_CAT(BOOST_PP_SEQ_ELEM(0, DATA), N))

#define METALOG_FOR_EACH_ARG(N, PREFIX, MACRO) \
    BOOST_PP_ENUM(N, METALOG_FORWARD_MACRO_FOR_EACH_ARG, (PREFIX)(MACRO))

#define METALOG_ARG(ARG) \
    ARG

#define METALOG_ARGS(N, PREFIX) \
    METALOG_FOR_EACH_ARG(N, PREFIX, METALOG_ARG)

#define METALOG_PARAM(PARAM) \
    typename PARAM

#define METALOG_PARAMS(N, PREFIX) \
    METALOG_FOR_EACH_ARG(N, PREFIX, METALOG_PARAM)

#define METALOG_OPTIONAL_PARAM(PARAM) \
    typename PARAM = detail::_

#define METALOG_OPTIONAL_PARAMS(N, PREFIX) \
    METALOG_FOR_EACH_ARG(N, PREFIX, METALOG_OPTIONAL_PARAM)

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
