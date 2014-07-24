/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _METALOG_SOLUTIONS_HPP_
#define _METALOG_SOLUTIONS_HPP_

#include "../types.hpp"

#include "../detail/preprocessor.hpp"

#include <boost/preprocessor/arithmetic/sub.hpp>

namespace metalog
{
    template
    <
            typename g, typename c, typename b, typename e, typename s,
            METALOG_VARIADIC_PARAMS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1), sT), typename seq2
    >
    struct join
            <
                resolve<g, c, b, e, s, METALOG_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1), sT)>, seq2
                METALOG_TRAILING_VARIADIC_EMPTY_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 2))
            > :
            join<typename resolve<g, c, b, e, s, METALOG_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1), sT)>::solution, seq2>
    {};

    template
    <
            typename g, typename c, typename b, typename e, typename s,
            METALOG_VARIADIC_PARAMS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1), sT), typename seq2
    >
    struct join
            <
                seq2, resolve<g, c, b, e, s, METALOG_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1), sT)>
                METALOG_TRAILING_VARIADIC_EMPTY_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 2))
            > :
            join<seq2, typename resolve<g, c, b, e, s, METALOG_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1), sT)>::solution>
    {};

    template
    <
            typename g1, typename c1, typename b1, typename e1, typename s1, METALOG_VARIADIC_PARAMS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1), sT1),
            typename g2, typename c2, typename b2, typename e2, typename s2, METALOG_VARIADIC_PARAMS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1), sT2)
    >
    struct join
            <
                resolve<g1, c1, b1, e1, s1, METALOG_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1), sT1)>,
                resolve<g2, c2, b2, e2, s2, METALOG_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1), sT2)>
                METALOG_TRAILING_VARIADIC_EMPTY_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 2))
            > :
            join
            <
                typename resolve<g1, c1, b1, e1, s1, METALOG_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1), sT1)>::solution,
                typename resolve<g2, c2, b2, e2, s2, METALOG_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1), sT2)>::solution
            >
    {};

    template
    <
            typename g, typename c, typename b, typename e, typename s, METALOG_VARIADIC_PARAMS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1), sT),
            typename seq2, METALOG_VARIADIC_PARAMS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 2), seqT)
    >
    struct join
            <
                resolve<g, c, b, e, s, METALOG_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1), sT)>,
                seq2, METALOG_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 2), seqT)
            > :
            join
            <
                typename resolve<g, c, b, e, s, METALOG_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1), sT)>::solution,
                seq2, METALOG_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 2), seqT)
            >
    {};

    template
    <
            typename g, typename c, typename b, typename e, typename s, METALOG_VARIADIC_PARAMS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1), sT),
            typename seq2, METALOG_VARIADIC_PARAMS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 2), seqT)
    >
    struct join
            <
                seq2, resolve<g, c, b, e, s, METALOG_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1), sT)>,
                METALOG_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 2), seqT)
            > :
            join
            <
                seq2, typename resolve<g, c, b, e, s, METALOG_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1), sT)>::solution,
                METALOG_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 2), seqT)
            >
    {};

    template
    <
            typename g1, typename c1, typename b1, typename e1, typename s1, METALOG_VARIADIC_PARAMS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1), sT1),
            typename g2, typename c2, typename b2, typename e2, typename s2, METALOG_VARIADIC_PARAMS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1), sT2),
            METALOG_VARIADIC_PARAMS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 2), seqT)
    >
    struct join
            <
                resolve<g1, c1, b1, e1, s1, METALOG_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1), sT1)>,
                resolve<g2, c2, b2, e2, s2, METALOG_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1), sT2)>,
                METALOG_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 2), seqT)
            > :
            join
            <
                typename resolve<g1, c1, b1, e1, s1, METALOG_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1), sT1)>::solution,
                typename resolve<g2, c2, b2, e2, s2, METALOG_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1), sT2)>::solution,
                METALOG_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 2), seqT)
            >
    {};
}

#endif
