/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#include <boost/config.hpp>

#ifndef METALOG_NO_VARIADIC_TEMPLATES
    #ifdef BOOST_NO_CXX11_VARIADIC_TEMPLATES
        #define METALOG_NO_VARIADIC_TEMPLATES 1
    #else
        #define METALOG_NO_VARIADIC_TEMPLATES 0
    #endif
#endif

#include <boost/mpl/limits/map.hpp>
#include <boost/mpl/limits/vector.hpp>

#ifndef METALOG_MAX_ARGS
    #include <boost/preprocessor/min.hpp>
    #define METALOG_MAX_ARGS BOOST_PP_MIN(BOOST_MPL_LIMIT_MAP_SIZE, BOOST_MPL_LIMIT_VECTOR_SIZE)
#endif

#if METALOG_MAX_ARGS > BOOST_MPL_LIMIT_MAP_SIZE
    #undef BOOST_MPL_LIMIT_MAP_SIZE
    #define BOOST_MPL_LIMIT_MAP_SIZE METALOG_MAX_ARGS
    #define BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif


#if METALOG_MAX_ARGS > BOOST_MPL_LIMIT_VECTOR_SIZE
    #undef BOOST_MPL_LIMIT_VECTOR_SIZE
    #define BOOST_MPL_LIMIT_VECTOR_SIZE METALOG_MAX_ARGS
    #define BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif

#include "preprocessor/args.hpp"
#include "preprocessor/variadic_args.hpp"




