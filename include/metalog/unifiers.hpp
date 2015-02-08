/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _METALOG_UNIFIERS_HPP_
#define _METALOG_UNIFIERS_HPP_

#include "config.hpp"

#include "detail/preprocessor.hpp"
#include "detail/collections.hpp"

namespace metalog
{
    template<METALOG_VARIADIC_OPTIONAL_PARAMS(METALOG_MAX_ARGS, _)>
    struct unifiers;
}

METALOG_DEFINE_COLLECTION(unifiers, ASSOCIATIVE)

#include "unifiers/polymorphic.hpp"

#endif
