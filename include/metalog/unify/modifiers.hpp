/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _METALOG_UNIFY_MODIFIERS_HPP_
#define _METALOG_UNIFY_MODIFIERS_HPP_

#include "../detail/preprocessor.hpp"

#include <boost/config.hpp>

#include <boost/preprocessor/arithmetic/sub.hpp>

#define METALOG_DEFINE_MODIFIER_UNIFICATION(MODIFIER) \
    template<typename lExpr, typename rExpr, typename u> \
    struct unify<lExpr MODIFIER, rExpr MODIFIER, u> : \
            unify<lExpr, rExpr, u> \
    {};

namespace metalog
{
    METALOG_DEFINE_MODIFIER_UNIFICATION(const)
    METALOG_DEFINE_MODIFIER_UNIFICATION(volatile)
    METALOG_DEFINE_MODIFIER_UNIFICATION(const volatile)
    METALOG_DEFINE_MODIFIER_UNIFICATION(*)
    METALOG_DEFINE_MODIFIER_UNIFICATION([])
    METALOG_DEFINE_MODIFIER_UNIFICATION(&)
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
    METALOG_DEFINE_MODIFIER_UNIFICATION(&&)
#endif

    template<typename lExpr, typename rExpr, std::size_t N, typename u>
    struct unify<lExpr[N], rExpr[N], u> :
            unify<lExpr, rExpr, u>
    {};
}

#undef METALOG_DEFINE_MODIFIER_UNIFICATION

#endif
