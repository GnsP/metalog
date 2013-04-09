/*
 * This file is part of munify, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _MUNIFY_UNIFY_ATOMS_HPP_
#define _MUNIFY_UNIFY_ATOMS_HPP_

#include <boost/mpl/bool.hpp>
#include <boost/type_traits.hpp>

namespace munify
{
    template<typename lExpr, typename rExpr, typename u>
    struct unify<atom<lExpr>, atom<rExpr>, u> :
            unifiable<boost::is_same<lExpr, rExpr>, u>
    {};
}

#endif
