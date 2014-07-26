/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _METALOG_JOIN_VARIADIC_HPP_
#define _METALOG_JOIN_VARIADIC_HPP_

#include "../detail/preprocessor.hpp"

namespace metalog
{
    template<typename h1, typename h2, METALOG_VARIADIC_PARAMS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 2), t)>
    struct join :
            join<typename join<h1, h2>::type, METALOG_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 2), t)>
    {};
}

#endif
