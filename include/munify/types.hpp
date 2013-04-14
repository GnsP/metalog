/*
 * This file is part of munify, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _MUNIFY_TYPES_HPP_
#define _MUNIFY_TYPES_HPP_

#include "detail/preprocessor.hpp"

#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/mpl/map.hpp>

namespace munify
{
    /**
     * Any expression wrapped by atom<> is considered to be a constant for the purpose of unification,
     * i.e. the unification of atom<A> with atom<B> succeeds iff A is literally equal to B,
     * regardless of variable substitutions or unwrapping of terms.
     */
    template<typename>
    struct atom;

    template<int n>
    struct var;

    template<typename, MUNIFY_VARIADIC_PARAMS_DECLARATION(BOOST_PP_SUB(MUNIFY_MAX_VARIADIC_ARGS, 1), _)>
    struct term;
}

#endif
