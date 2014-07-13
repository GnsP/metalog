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
    template<typename, typename>
    struct join;

    template<>
    struct join
            <
                conjunction<METALOG_VARIADIC_EMPTY_ARGS(METALOG_MAX_VARIADIC_ARGS)>,
                conjunction<METALOG_VARIADIC_EMPTY_ARGS(METALOG_MAX_VARIADIC_ARGS)>
            > :
        boost::mpl::identity<conjunction<> >
    {};

    template<METALOG_VARIADIC_PARAMS(METALOG_MAX_VARIADIC_ARGS, _)>
    struct join
            <
                conjunction<METALOG_VARIADIC_EMPTY_ARGS(METALOG_MAX_VARIADIC_ARGS)>,
                conjunction<METALOG_VARIADIC_ARGS(METALOG_MAX_VARIADIC_ARGS, _)>
            > :
        boost::mpl::identity<conjunction<METALOG_VARIADIC_ARGS(METALOG_MAX_VARIADIC_ARGS, _)> >
    {};

    template<METALOG_VARIADIC_PARAMS(METALOG_MAX_VARIADIC_ARGS, _)>
    struct join
            <
                conjunction<METALOG_VARIADIC_ARGS(METALOG_MAX_VARIADIC_ARGS, _)>,
                conjunction<METALOG_VARIADIC_EMPTY_ARGS(METALOG_MAX_VARIADIC_ARGS)>
            > :
        join
        <
            conjunction<>,
            conjunction<METALOG_VARIADIC_ARGS(METALOG_MAX_VARIADIC_ARGS, _)>
        >
    {};

    template
    <
            typename lH,
            METALOG_VARIADIC_PARAMS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1), lT),
            METALOG_VARIADIC_PARAMS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1), rH)
    >
    struct join
            <
                conjunction<lH, METALOG_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1), lT)>,
                conjunction<METALOG_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1), rH) METALOG_TRAILING_VARIADIC_EMPTY_ARGS(1)>
            > :
        join
        <
            conjunction<METALOG_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1), lT)>,
            conjunction<lH, METALOG_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1), rH)>
        >
    {};
}

#endif
