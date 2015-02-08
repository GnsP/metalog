/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _METALOG_UNIFIERS_POLYMORPHIC_HPP_
#define _METALOG_UNIFIERS_POLYMORPHIC_HPP_

#include "../unify.hpp"

#include "../detail/lazy.hpp"

namespace metalog
{

    template<typename lExpr, typename rExpr, typename u>
    struct unifiers<unify<lExpr, rExpr, u> > :
            unify<lExpr, rExpr, u>::unifiers
    {};

    template<typename expr>
    struct unifiers<detail::lazy<expr> > :
            unifiers<typename detail::lazy<expr>::type>
    {};
}

#endif
