/*
 * This file is part of munify, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _MUNIFY_UNIFY_MODIFIERS_HPP_
#define _MUNIFY_UNIFY_MODIFIERS_HPP_

#include "../types.hpp"

#include <boost/config.hpp>

namespace munify
{
#define MUNIFY_DEFINE_MODIFIER_UNIFICATION(MODIFIER) \
    template<typename lExpr, typename rExpr, typename u> \
    struct unify<lExpr MODIFIER, rExpr MODIFIER, u> : \
            unify<lExpr, rExpr, u> \
    {};

    MUNIFY_DEFINE_MODIFIER_UNIFICATION(const)
    MUNIFY_DEFINE_MODIFIER_UNIFICATION(volatile)
    MUNIFY_DEFINE_MODIFIER_UNIFICATION(const volatile)
    MUNIFY_DEFINE_MODIFIER_UNIFICATION(*)
    MUNIFY_DEFINE_MODIFIER_UNIFICATION([])
    MUNIFY_DEFINE_MODIFIER_UNIFICATION(&)
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
    MUNIFY_DEFINE_MODIFIER_UNIFICATION(&&)
#endif

    template<typename lExpr, typename rExpr, std::size_t N, typename u>
    struct unify<lExpr[N], rExpr[N], u > :
            unify<lExpr, rExpr, u>
    {};
}

#endif
