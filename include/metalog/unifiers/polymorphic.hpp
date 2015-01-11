/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _METALOG_UNIFIERS_POLYMORPHIC_HPP_
#define _METALOG_UNIFIERS_POLYMORPHIC_HPP_

#include "../unify.hpp"
#include "../join.hpp"
#include "../preprocessor.hpp"

#include "../detail/lazy.hpp"

#include <boost/mpl/identity.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/map.hpp>

namespace metalog
{
    template<typename m>
    struct unifiers<m> :
            boost::mpl::identity<unifiers<m> >
    {
        typedef m map;
    };

    template<typename key, typename value>
    struct unifiers<boost::mpl::pair<key, value> > :
            unifiers<boost::mpl::map<boost::mpl::pair<key, value> > >
    {};

    template<typename u>
    struct unifiers<unifiers<u> > :
            unifiers<u>
    {};

    template<typename lExpr, typename rExpr, typename uH, METALOG_VARIADIC_PARAMS(BOOST_PP_SUB(METALOG_MAX_ARGS, 1), uT)>
    struct unifiers<unify<lExpr, rExpr, uH, METALOG_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_ARGS, 1), uT)> > :
            unify<lExpr, rExpr, uH, METALOG_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_ARGS, 1), uT)>::unifiers
    {};

    template<typename expr>
    struct unifiers<detail::lazy<expr> > :
            unifiers<typename detail::lazy<expr>::type>
    {};

    //should be handled by the lazy specialization
    template<typename uH1, typename uH2, METALOG_VARIADIC_PARAMS(BOOST_PP_SUB(METALOG_MAX_ARGS, 2), uT)>
    struct unifiers<join<uH1, uH2, METALOG_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_ARGS, 2), uT)> > :
        join<uH1, uH2, METALOG_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_ARGS, 2), uT)>::type
    {};
}

#endif
