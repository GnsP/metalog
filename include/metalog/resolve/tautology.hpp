/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _METALOG_RESOLVE_TAUTOLOGY_HPP_
#define _METALOG_RESOLVE_TAUTOLOGY_HPP_

#include "../detail/preprocessor.hpp"

#include <boost/preprocessor/arithmetic/sub.hpp>

#include <boost/mpl/logical.hpp>

namespace metalog
{
    template<typename clauses, typename it, typename s>
    struct resolve
            <
                conjunction<METALOG_VARIADIC_EMPTY_ARGS(METALOG_MAX_VARIADIC_ARGS)>,
                clauses, it, it, s METALOG_TRAILING_VARIADIC_EMPTY_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1))
            > :
            boost::mpl::true_
    {
        typedef s solution;
    };

    template<typename clauses, typename begin, typename end, typename s>
    struct resolve
            <
                conjunction<METALOG_VARIADIC_EMPTY_ARGS(METALOG_MAX_VARIADIC_ARGS)>,
                clauses, begin, end, s METALOG_TRAILING_VARIADIC_EMPTY_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1))
            > :
            resolve<conjunction<>, clauses, end, end, s>
    {};
}

#endif
