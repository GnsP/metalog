/*
 * This file is part of munify, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _MUNIFY_MODIFIERS_HPP_
#define _MUNIFY_MODIFIERS_HPP_

namespace munify
{
    template<typename lExpr, typename rExpr, typename u>
    struct unify<lExpr*, rExpr*, u > :
            unify<lExpr, rExpr, u>
    {};

    template<typename lExpr, typename rExpr, typename u>
    struct unify<lExpr&, rExpr&, u > :
            unify<lExpr, rExpr, u>
    {};

    template<typename lExpr, typename rExpr, typename u>
    struct unify<lExpr&&, rExpr&&, u > :
            unify<lExpr, rExpr, u>
    {};

    template<typename lExpr, typename rExpr, typename u>
    struct unify<lExpr const, rExpr const, u > :
            unify<lExpr, rExpr, u>
    {};

    template<typename lExpr, typename rExpr, typename u>
    struct unify<lExpr volatile, rExpr volatile, u > :
            unify<lExpr, rExpr, u>
    {};

    template<typename lExpr, typename rExpr, typename u>
    struct unify<lExpr const volatile, rExpr  const volatile, u > :
            unify<lExpr, rExpr, u>
    {};
}

#endif
