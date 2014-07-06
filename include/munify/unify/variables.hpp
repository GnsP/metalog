/*
 * This file is part of munify, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _MUNIFY_UNIFY_VARIABLES_HPP_
#define _MUNIFY_UNIFY_VARIABLES_HPP_

#include "../detail/empty.hpp"

#include <boost/mpl/bool.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/map.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/apply_wrap.hpp>

namespace munify
{
    template<typename n, typename expr, typename u>
    struct unify<var<n>, expr, u> :
            boost::mpl::if_
            <
                boost::mpl::has_key<u, var<n> >,
                unify<typename boost::mpl::apply_wrap1<substitute<u>, var<n> >::type, typename boost::mpl::apply_wrap1<substitute<u>, expr>::type, u>,
                unify //occurs check
                <
                    atom<typename boost::mpl::apply_wrap1<substitute<u>, expr>::type>,
                    atom<typename boost::mpl::apply_wrap1<substitute<typename boost::mpl::insert<u, boost::mpl::pair<var<n>, detail::_> >::type>, expr>::type>,
                    typename boost::mpl::insert<u, boost::mpl::pair<var<n>, expr> >::type
                >
            >::type
    {};

    template<typename n, typename expr, typename u>
    struct unify<expr, var<n>, u> :
            unify<var<n>, expr, u>
    {};

    template<typename m, typename n, typename u>
    struct unify<var<m>, var<n>, u> :
            boost::mpl::if_
            <
                boost::mpl::or_<boost::mpl::has_key<u, var<m> >, boost::mpl::has_key<u, var<n> > >,
                unify<typename boost::mpl::apply_wrap1<substitute<u>, var<m> >::type, typename boost::mpl::apply_wrap1<substitute<u>, var<n> >::type, u>,
                unify<var<n>, var<n>, typename boost::mpl::insert<u, boost::mpl::pair<var<m>, var<n> > >::type>
            >::type
    {};

    template<typename n, typename u>
    struct unify<var<n>, var<n>, u> :
            unify<atom<var<n> >, atom<var<n> >, u>
    {};
}

#endif
