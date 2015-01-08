/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _METALOG_UNIFY_VARIABLES_HPP_
#define _METALOG_UNIFY_VARIABLES_HPP_

#include "../detail/empty.hpp"
#include "../detail/lazy.hpp"
#include "../detail/preprocessor.hpp"

#include <boost/preprocessor/arithmetic/sub.hpp>

#include <boost/mpl/pair.hpp>
#include <boost/mpl/map.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/bind.hpp>
#include <boost/mpl/quote.hpp>

namespace metalog
{
    template<typename n, typename u>
    struct unify<var<n>, var<n>, u> :
            unify<atom<var<n> >, atom<var<n> >, u>
    {};

    template<typename m, typename n, typename u>
    struct unify<var<m>, var<n>, u> :
            boost::mpl::if_
            <
                boost::mpl::or_<boost::mpl::has_key<u, var<m> >, boost::mpl::has_key<u, var<n> > >,
                unify<detail::lazy<boost::mpl::bind<substitute<u>, var<m> > >, detail::lazy<boost::mpl::bind<substitute<u>, var<n> > >, u>,
                unify<atom<detail::_>, atom<detail::_>, u, boost::mpl::map<boost::mpl::pair<var<m>, var<n> > > >
            >::type
    {};

    template<typename n, typename expr, typename u>
    struct unify<var<n>, expr, u> :
            boost::mpl::if_
            <
                boost::mpl::has_key<u, var<n> >,
                unify<detail::lazy<boost::mpl::bind<substitute<u>, var<n> > >, detail::lazy<boost::mpl::bind<substitute<u>, expr> >, u>,
                unify //occurs check
                <
                    detail::lazy<boost::mpl::bind<boost::mpl::quote1<atom>, boost::mpl::bind<substitute<u>, expr> > >,
                    detail::lazy<boost::mpl::bind<boost::mpl::quote1<atom>, boost::mpl::bind<substitute<u, boost::mpl::map<boost::mpl::pair<var<n>, detail::_> > >, expr> > >,
                    u, boost::mpl::map<boost::mpl::pair<var<n>, expr> >
                >
            >::type
    {};

    template<typename n, typename expr, typename u>
    struct unify<expr, var<n>, u> :
            unify<var<n>, expr, u>
    {};

    template<typename n, typename expr, typename u>
    struct unify<var<n>, detail::lazy<expr>, u> :
            unify<var<n>, typename detail::lazy<expr>::type, u>
    {};
}

#endif
