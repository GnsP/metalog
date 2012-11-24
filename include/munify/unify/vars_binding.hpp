/*
 * This file is part of munify, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _MUNIFY_VARS_BINDING_HPP_
#define _MUNIFY_VARS_BINDING_HPP_

#include <boost/mpl/bool.hpp>
#include <boost/mpl/arg.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/map.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/insert.hpp>

namespace munify
{
#warning occurs check

    template<int n, typename expr>
    struct unify<boost::mpl::arg<n>, expr, boost::mpl::map<> > :
            public unifiable<boost::mpl::true_, boost::mpl::map<boost::mpl::pair<boost::mpl::arg<n>, expr> > >
    {};

    template<int n, typename expr, typename u>
    class unify<boost::mpl::arg<n>, expr, u> :
            public substitute<u>::template apply<unify<boost::mpl::arg<n>, expr> >::type
    {
        private:
            typedef typename substitute<u>::template apply<unify<boost::mpl::arg<n>, expr> >::type forwarded;

        public:
            typedef typename boost::mpl::fold<typename forwarded::unifiers, u, boost::mpl::insert<boost::mpl::_1, boost::mpl::_2> >::type unifiers;
    };

    template<int n, typename expr, typename u>
    struct unify<expr, boost::mpl::arg<n>, u> :
            public unify<boost::mpl::arg<n>, expr, u>
    {};

    template<int m, int n>
    struct unify<boost::mpl::arg<m>, boost::mpl::arg<n>, boost::mpl::map<> > :
            public unifiable<boost::mpl::true_, boost::mpl::map<boost::mpl::pair<boost::mpl::arg<m>, boost::mpl::arg<n> > > >
    {};

    template<int m, int n, typename u>
    struct unify<boost::mpl::arg<m>, boost::mpl::arg<n>, u> :
            public substitute<u>::template apply<unify<boost::mpl::arg<m>, boost::mpl::arg<n> > >::type
    {
        private:
            typedef typename substitute<u>::template apply<unify<boost::mpl::arg<m>, boost::mpl::arg<n> > >::type forwarded;

        public:
            typedef typename boost::mpl::fold<typename forwarded::unifiers, u, boost::mpl::insert<boost::mpl::_1, boost::mpl::_2> >::type unifiers;
    };

    template<int n, typename u>
    struct unify<boost::mpl::arg<n>, boost::mpl::arg<n>, u> :
            public unifiable<boost::mpl::true_, u>
    {};

    template<int n>
    struct unify<boost::mpl::arg<n>, boost::mpl::arg<n>, boost::mpl::map<> > :
            public unifiable<boost::mpl::true_>
    {};
}

#endif
