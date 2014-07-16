/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _METALOG_UNIFY_ATOMS_HPP_
#define _METALOG_UNIFY_ATOMS_HPP_

#include "../minimize.hpp"

#include "../detail/lazy.hpp"

#include <boost/mpl/bool.hpp>
#include <boost/mpl/map.hpp>
#include <boost/mpl/apply_wrap.hpp>

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

    template<typename lExpr, typename rExpr, typename u>
    struct unify<atom<detail::lazy<lExpr> >, atom<rExpr>, u> :
            unify<atom<typename boost::mpl::apply_wrap0<lExpr>::type>, atom<rExpr>, u>
    {};

    template<typename lExpr, typename rExpr, typename u>
    struct unify<atom<lExpr>, atom<detail::lazy<rExpr> >, u> :
            unify<atom<lExpr>, atom<typename boost::mpl::apply_wrap0<rExpr>::type>, u>
    {};

    template<typename lExpr, typename rExpr, typename u>
    struct unify<atom<detail::lazy<lExpr> >, atom<detail::lazy<rExpr> >, u> :
            unify<atom<typename boost::mpl::apply_wrap0<lExpr>::type>, atom<typename boost::mpl::apply_wrap0<rExpr>::type>, u>
    {};
}

#endif
