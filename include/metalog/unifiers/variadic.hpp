/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _METALOG_UNIFIERS_VARIADIC_HPP_
#define _METALOG_UNIFIERS_VARIADIC_HPP_

#include "../join.hpp"

#include "../detail/preprocessor.hpp"

#include <boost/preprocessor/arithmetic/sub.hpp>

#define METALOG_FORWARD_CAST(ARG) \
    unifiers<ARG>

namespace metalog
{
    template<typename uH, METALOG_VARIADIC_PARAMS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1), uT)>
    struct unifiers :
        unifiers<join<METALOG_FORWARD_CAST(uH) METALOG_FOR_EACH_TRAILING_VARIADIC_ARG(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1), uT, METALOG_FORWARD_CAST)> >
    {};
}

#undef METALOG_FORWARD_CAST

#endif
