/*
 * This file is part of munify, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _MUNIFY_UNIFY_HPP_
#define _MUNIFY_UNIFY_HPP_

#include "substitute.hpp"

#include <boost/mpl/bool.hpp>
#include <boost/mpl/map.hpp>
#include <boost/type_traits.hpp>

namespace munify
{
    //base: unification of constants
    template<typename lExpr, typename rExpr, typename u = boost::mpl::map<> >
    struct unify : public boost::mpl::bool_<boost::is_same<lExpr, rExpr>::value>
    {
            typedef boost::mpl::map<> unifiers;
    };
}

#include "equiv_transform.hpp"
#include "modifiers_unwrapping.hpp"
#include "rels_unwrapping.hpp"
#include "vars_binding.hpp"

#endif
