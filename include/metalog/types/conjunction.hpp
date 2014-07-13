/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _METALOG_CONJUNCTION_HPP_
#define _METALOG_CONJUNCTION_HPP_

#include "../detail/preprocessor.hpp"

#include <boost/preprocessor/arithmetic/sub.hpp>

#include <boost/mpl/identity.hpp>

namespace metalog
{
    template<typename, METALOG_VARIADIC_PARAMS_DECLARATION(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1), cT)>
    struct join;

    template<typename c>
    struct join<c METALOG_TRAILING_VARIADIC_EMPTY_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1))> :
        boost::mpl::identity<c>
    {};

    template<METALOG_VARIADIC_PARAMS(METALOG_MAX_VARIADIC_ARGS, _) METALOG_TRAILING_VARIADIC_PARAMS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 2), cT)>
    struct join
            <
                conjunction<METALOG_VARIADIC_EMPTY_ARGS(METALOG_MAX_VARIADIC_ARGS)>,
                conjunction<METALOG_VARIADIC_ARGS(METALOG_MAX_VARIADIC_ARGS, _)>
                METALOG_TRAILING_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 2), cT)
            > :
        join
        <
            conjunction<METALOG_VARIADIC_ARGS(METALOG_MAX_VARIADIC_ARGS, _)>
            METALOG_TRAILING_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 2), cT)
        >
    {};

    template<METALOG_VARIADIC_PARAMS(METALOG_MAX_VARIADIC_ARGS, _) METALOG_TRAILING_VARIADIC_PARAMS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 2), cT)>
    struct join
            <
                conjunction<METALOG_VARIADIC_ARGS(METALOG_MAX_VARIADIC_ARGS, _)>,
                conjunction<METALOG_VARIADIC_EMPTY_ARGS(METALOG_MAX_VARIADIC_ARGS)>
                METALOG_TRAILING_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 2), cT)
            > :
        join
        <
            conjunction<METALOG_VARIADIC_ARGS(METALOG_MAX_VARIADIC_ARGS, _)>
            METALOG_TRAILING_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 2), cT)
        >
    {};

    template
    <
            typename lH,
            METALOG_VARIADIC_PARAMS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1), lT),
            METALOG_VARIADIC_PARAMS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1), rH)
            METALOG_TRAILING_VARIADIC_PARAMS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 2), cT)
    >
    struct join
            <
                conjunction<lH, METALOG_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1), lT)>,
                conjunction<METALOG_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1), rH) METALOG_TRAILING_VARIADIC_EMPTY_ARGS(1)>
                METALOG_TRAILING_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 2), cT)
            > :
        join
        <
            conjunction<METALOG_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1), lT)>,
            conjunction<lH, METALOG_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1), rH)>
            METALOG_TRAILING_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 2), cT)
        >
    {};
}

#endif
