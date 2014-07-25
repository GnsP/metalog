/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _METALOG_JOIN_HPP_
#define _METALOG_JOIN_HPP_

#include "detail/preprocessor.hpp"

namespace metalog
{
    template<typename, typename, METALOG_VARIADIC_PARAMS_DECLARATION(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 2), _)>
    struct join;
}

#include "join/conjunction.hpp"
#include "join/sequences.hpp"
#include "join/solutions.hpp"
#include "join/variadic.hpp"

#endif
