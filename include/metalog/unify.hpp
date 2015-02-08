/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _METALOG_UNIFY_HPP_
#define _METALOG_UNIFY_HPP_

#include "unifiers.hpp"

namespace metalog
{
    template
    <
            typename lExpr,
            typename rExpr,
            typename u = unifiers<>
    >
    struct unify;
}

#include "unify/atoms.hpp"
#include "unify/lazy.hpp"
#include "unify/modifiers.hpp"
#include "unify/terms.hpp"
#include "unify/variables.hpp"

#endif
