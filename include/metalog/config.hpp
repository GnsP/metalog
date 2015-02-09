/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _METALOG_CONFIG_HPP_
#define _METALOG_CONFIG_HPP_

#include "config/workaround/boost7769.hpp"
#include "config/workaround/boost11001.hpp"

#include <boost/config.hpp>

#ifndef METALOG_NO_VARIADIC_TEMPLATES
    #ifdef BOOST_NO_CXX11_VARIADIC_TEMPLATES
        #define METALOG_NO_VARIADIC_TEMPLATES 1
    #else
        #define METALOG_NO_VARIADIC_TEMPLATES 0
    #endif
#endif

#include <boost/mpl/limits/arity.hpp>
#include <boost/mpl/limits/map.hpp>
#include <boost/mpl/limits/vector.hpp>

#ifndef METALOG_MAX_ARGS
    #include <boost/preprocessor/min.hpp>
    #define METALOG_MAX_ARGS \
        BOOST_PP_MIN \
        ( \
            BOOST_PP_MIN \
            ( \
                BOOST_MPL_LIMIT_MAP_SIZE, \
                BOOST_MPL_LIMIT_VECTOR_SIZE \
            ), \
            BOOST_MPL_LIMIT_METAFUNCTION_ARITY \
        )
#endif

#if METALOG_MAX_ARGS > BOOST_MPL_LIMIT_METAFUNCTION_ARITY
    #undef BOOST_MPL_LIMIT_METAFUNCTION_ARITY
    #define BOOST_MPL_LIMIT_METAFUNCTION_ARITY METALOG_MAX_ARGS
    #define BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif

#if METALOG_MAX_ARGS > BOOST_MPL_LIMIT_MAP_SIZE
    #include <boost/preprocessor/arithmetic.hpp>
    #undef BOOST_MPL_LIMIT_MAP_SIZE
    #define BOOST_MPL_LIMIT_MAP_SIZE \
        BOOST_PP_MUL(BOOST_PP_INC(BOOST_PP_DIV(METALOG_MAX_ARGS, 10)), 10)
    #define BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif

#if METALOG_MAX_ARGS > BOOST_MPL_LIMIT_VECTOR_SIZE
    #include <boost/preprocessor/arithmetic.hpp>
    #undef BOOST_MPL_LIMIT_VECTOR_SIZE
    #define BOOST_MPL_LIMIT_VECTOR_SIZE \
        BOOST_PP_MUL(BOOST_PP_INC(BOOST_PP_DIV(METALOG_MAX_ARGS, 10)), 10)
    #define BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif

#endif
