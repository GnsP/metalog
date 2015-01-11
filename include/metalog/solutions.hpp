/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _METALOG_SOLUTIONS_HPP_
#define _METALOG_SOLUTIONS_HPP_

#include "resolve.hpp"

#include "detail/preprocessor.hpp"

#include <boost/mpl/identity.hpp>

namespace metalog
{
    template<typename>
    struct solution;

    template
    <
            typename goal, typename clauses, typename begin, typename end, typename s,
            METALOG_VARIADIC_PARAMS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1), sT)
    >
    struct solution<resolve<goal, clauses, begin, end, s, METALOG_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1), sT)> > :
        boost::mpl::identity<typename resolve<goal, clauses, begin, end, s, METALOG_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1), sT)>::solution>
    {};

    template<typename s>
    struct solution<solution<s> > :
            solution<s>
    {};
}

#endif
