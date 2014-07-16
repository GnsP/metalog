/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _METALOG_UNIFY_HPP_
#define _METALOG_UNIFY_HPP_

#include "types.hpp"

#include <boost/mpl/map.hpp>

namespace metalog
{
    template<typename lExpr, typename rExpr, typename u = boost::mpl::map<> >
    struct unify :
            unify<atom<lExpr>, atom<rExpr>, u>
    {};
}

#include "unify/lazy.hpp"
#include "unify/modifiers.hpp"
#include "unify/atoms.hpp"
#include "unify/variables.hpp"
#include "unify/terms.hpp"

#endif
