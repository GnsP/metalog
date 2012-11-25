/*
 * This file is part of munify, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _MUNIFY_UNIFY_HPP_
#define _MUNIFY_UNIFY_HPP_

#include "types.hpp"
#include "unifiable.hpp"
#include "substitute.hpp"
#include "occurs.hpp"

#include <boost/mpl/map.hpp>
#include <boost/type_traits.hpp>

namespace munify
{
    template<typename lExpr, typename rExpr, typename u = boost::mpl::map<> >
    struct unify :
            public unifiable<boost::is_same<lExpr, rExpr>, u>
    {};
}

#include "unify/equiv_transform.hpp"
#include "unify/modifiers.hpp"
#include "unify/terms.hpp"
#include "unify/vars_binding.hpp"

#endif
