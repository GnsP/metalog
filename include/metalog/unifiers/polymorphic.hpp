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

#include <boost/preprocessor/arithmetic/sub.hpp>

#include <boost/mpl/identity.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/map.hpp>

namespace metalog
{
    template<typename seq>
    struct unifiers<seq> :
            boost::mpl::identity<unifiers<seq> >
    {
        METALOG_DEFINE_IMPL(metalog::unifiers, seq)
    };

    template<typename h, METALOG_VARIADIC_PARAMS(BOOST_PP_SUB(METALOG_MAX_ARGS, 1), t)>
    struct unifiers<unifiers<h, METALOG_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_ARGS, 1), t)> > :
            unifiers<h, METALOG_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_ARGS, 1), t)>
    {};

    template<typename lExpr, typename rExpr, typename u>
    struct unifiers<unify<lExpr, rExpr, u> > :
            unify<lExpr, rExpr, u>::unifiers
    {};

    template<typename key, typename value>
    struct unifiers<boost::mpl::pair<key, value> > :
            unifiers<boost::mpl::map<boost::mpl::pair<key, value> > >
    {};

    template<typename expr>
    struct unifiers<detail::lazy<expr> > :
            unifiers<typename detail::lazy<expr>::type>
    {};
}

#endif
