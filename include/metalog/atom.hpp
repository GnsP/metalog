/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _METALOG_ATOM_HPP_
#define _METALOG_ATOM_HPP_

#include "config.hpp"

#include <boost/mpl/identity.hpp>

namespace metalog
{
    /**
     * An atom is considered to be a constant for the purpose of unification.
     * The unification of atom<A> with atom<B> succeeds iff A is literally equal to B,
     * regardless of variable substitutions.
     */
    template<typename expr>
    struct atom :
            boost::mpl::identity<atom<expr> >
    {};

    template<typename expr>
    struct atom<atom<expr> > :
            atom<expr>
    {};
}

#endif
