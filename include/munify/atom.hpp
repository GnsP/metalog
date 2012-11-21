/*
 * This file is part of munify, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _MUNIFY_ATOM_HPP_
#define _MUNIFY_ATOM_HPP_

namespace munify
{
    /**
     * Any expression wraped by atom<> is considered to be a constant for the purpose of unification
     */
    template<typename h, typename... t>
    struct atom;
}

#endif
