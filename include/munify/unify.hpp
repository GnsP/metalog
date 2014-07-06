/*
 * This file is part of munify, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _MUNIFY_UNIFY_HPP_
#define _MUNIFY_UNIFY_HPP_

#include "types.hpp"
#include "substitute.hpp"

#include <boost/mpl/map.hpp>

namespace munify
{
    template<typename lExpr, typename rExpr, typename u = boost::mpl::map<> >
    struct unify :
            unify<atom<lExpr>, atom<rExpr>, u>
    {};
}

#include "unify/modifiers.hpp"
#include "unify/atoms.hpp"
#include "unify/variables.hpp"
#include "unify/terms.hpp"

#endif
