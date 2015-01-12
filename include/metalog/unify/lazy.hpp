/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _METALOG_UNIFY_LAZY_HPP_
#define _METALOG_UNIFY_LAZY_HPP_

#include "../detail/lazy.hpp"

#include <boost/preprocessor/arithmetic/sub.hpp>

namespace metalog
{
    template<typename lExpr, typename rExpr, typename u>
    struct unify<detail::lazy<lExpr>, rExpr, u>:
            unify<typename detail::lazy<lExpr>::type, rExpr, u>
    {};

    template<typename lExpr, typename rExpr, typename u>
    struct unify<lExpr, detail::lazy<rExpr>, u>:
            unify<lExpr, typename detail::lazy<rExpr>::type, u>
    {};

    template<typename lExpr, typename rExpr, typename u>
    struct unify<detail::lazy<lExpr>, detail::lazy<rExpr>, u>:
            unify<typename detail::lazy<lExpr>::type, typename detail::lazy<rExpr>::type, u>
    {};
}

#endif
