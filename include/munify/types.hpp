/*
 * This file is part of munify, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _MUNIFY_TYPES_HPP_
#define _MUNIFY_TYPES_HPP_

namespace munify
{
    /**
     * Any expression wrapped by atom<> is considered to be a constant for the purpose of unification
     */
    template<typename, typename...>
    struct atom;

    template<int n>
    struct var;

    template<typename, typename...>
    struct term;
}

#endif