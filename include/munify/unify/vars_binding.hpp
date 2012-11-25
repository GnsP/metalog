/*
 * This file is part of munify, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _MUNIFY_VARS_BINDING_HPP_
#define _MUNIFY_VARS_BINDING_HPP_

#include <boost/mpl/bool.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/map.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/mpl/if.hpp>

namespace munify
{
    template<int n, typename expr, typename u>
    class unify<var<n>, expr, u> :
            public boost::mpl::if_
            <
                boost::mpl::has_key<u, var<n> >,
                unify<typename substitute<u>::template apply<var<n> >::type, typename substitute<u>::template apply<expr>::type, u>,
                unifiable<boost::mpl::not_<occurs<var<n>, expr> >, typename boost::mpl::insert<u, boost::mpl::pair<var<n>, expr> >::type>
            >::type
    {};

    template<int n, typename expr, typename u>
    struct unify<expr, var<n>, u> :
            public unify<var<n>, expr, u>
    {};

    template<int m, int n, typename u>
    struct unify<var<m>, var<n>, u> :
            public boost::mpl::if_
            <
                boost::mpl::has_key<u, var<m> >,
                unify<typename substitute<u>::template apply<var<m> >::type, typename substitute<u>::template apply<var<n> >::type, u>,
                unifiable<boost::mpl::not_<occurs<var<m>, var<n> > >, typename boost::mpl::insert<u, boost::mpl::pair<var<m>, var<n> > >::type>
            >::type
    {};

    template<int n, typename u>
    struct unify<var<n>, var<n>, u> :
            public unifiable<boost::mpl::true_, u>
    {};
}

#endif
