/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _METALOG_UNIFIERS_POLYMORPHIC_HPP_
#define _METALOG_UNIFIERS_POLYMORPHIC_HPP_

#include "../unify.hpp"

#include "../detail/lazy.hpp"
#include "../detail/sequences.hpp"
#include "../detail/preprocessor.hpp"

#include <boost/mpl/pair.hpp>
#include <boost/mpl/map.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/insert.hpp>

namespace metalog
{
    template<typename seq>
    struct unifiers<detail::seq::seq<seq> > :
            boost::mpl::identity<unifiers<detail::seq::seq<seq> > >
    {
        typedef detail::seq::seq<seq> impl;
    };

    template<>
    struct unifiers<> :
            unifiers<detail::seq::seq<boost::mpl::map<> > >
    {};

    template<METALOG_VARIADIC_PARAMS(METALOG_MAX_ARGS, _)>
    struct unifiers<unifiers<METALOG_VARIADIC_ARGS(METALOG_MAX_ARGS, _)> > :
            unifiers<METALOG_VARIADIC_ARGS(METALOG_MAX_ARGS, _)>
    {};

    template<typename lExpr, typename rExpr, typename u>
    struct unifiers<unify<lExpr, rExpr, u> > :
            unify<lExpr, rExpr, u>::unifiers
    {};

    template<typename key, typename value>
    struct unifiers<boost::mpl::pair<key, value> > :
            boost::mpl::insert<unifiers<>, boost::mpl::pair<key, value> >::type
    {};

    template<typename expr>
    struct unifiers<detail::lazy<expr> > :
            unifiers<typename detail::lazy<expr>::type>
    {};
}

#endif
