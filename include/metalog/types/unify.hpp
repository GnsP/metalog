/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _METALOG_TYPES_UNIFY_HPP_
#define _METALOG_TYPES_UNIFY_HPP_

#include "../detail/preprocessor.hpp"

#include <boost/mpl/identity.hpp>

namespace metalog
{
    template<typename unify>
    struct unifiers;

    template
    <
            typename lExpr, typename rExpr, typename u,
            METALOG_VARIADIC_PARAMS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1), uT)
    >
    struct unifiers<unify<lExpr, rExpr, u, METALOG_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1), uT)> > :
        boost::mpl::identity<typename unify<lExpr, rExpr, u, METALOG_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1), uT)>::unifiers>
    {};
}

#endif
