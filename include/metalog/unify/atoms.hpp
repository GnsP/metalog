/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _METALOG_UNIFY_ATOMS_HPP_
#define _METALOG_UNIFY_ATOMS_HPP_

#include "../minimize.hpp"

#include <boost/mpl/bool.hpp>
#include <boost/mpl/map.hpp>

namespace metalog
{
    template<typename lExpr, typename rExpr, typename u>
    struct unify<atom<lExpr>, atom<rExpr>, u> :
            boost::mpl::false_
    {
        typedef boost::mpl::map<> unifiers;
    };

    template<typename expr, typename u>
    struct unify<atom<expr>, atom<expr>, u> :
            boost::mpl::true_
    {
        typedef typename minimize<u>::type unifiers;
    };
}

#endif
