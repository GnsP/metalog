/*
 * This file is part of munify, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _MUNIFY_ATOMS_HPP_
#define _MUNIFY_ATOMS_HPP_

#include <boost/mpl/bool.hpp>

namespace munify
{
     template<typename hExpr, typename... tExpr, typename u>
    struct unify<atom<hExpr, tExpr...>, atom<hExpr, tExpr...>, u> :
            public unifiable<boost::mpl::true_, u>
    {};

    template<typename expr, typename u>
    struct unify<atom<expr>, expr, u> : unify<atom<expr>, atom<expr>, u>
    {};

    template<typename expr, typename u>
    struct unify<expr, atom<expr>, u> : unify<atom<expr>, expr, u>
    {};
}

#endif
