/*
 * This file is part of munify, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _MUNIFY_VARS_BINDING_HPP_
#define _MUNIFY_VARS_BINDING_HPP_

#include "unify.hpp"

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
    template<int n, typename expr>
    struct unify<boost::mpl::arg<n>, expr, boost::mpl::map<> > : public boost::mpl::true_
    {
            //TODO: occurs check
            typedef boost::mpl::map<boost::mpl::pair<boost::mpl::arg<n>, expr> > unifiers;
    };

    template<int n, typename expr, typename u>
    class unify<boost::mpl::arg<n>, expr, u> : public unify<typename substitute<u, boost::mpl::arg<n> >::type, typename substitute<u, expr>::type >
    {
        private:
            typedef typename unify<typename substitute<u, boost::mpl::arg<n> >::type, typename substitute<u, expr>::type>::unifiers tUnifiers;

        public:
            typedef typename boost::mpl::if_
            <
                unify,
                typename boost::mpl::fold<typename unify::tUnifiers, u, boost::mpl::insert<boost::mpl::_1, boost::mpl::_2> >::type,
                boost::mpl::map<>
            >::type unifiers;
    };

    template<int n, typename expr, typename u>
    struct unify<expr, boost::mpl::arg<n>, u> : public unify<boost::mpl::arg<n>, expr, u>
    {};

    template<int m, int n>
    struct unify<boost::mpl::arg<m>, boost::mpl::arg<n>, boost::mpl::map<> > : public boost::mpl::true_
    {
            typedef boost::mpl::map<boost::mpl::pair<boost::mpl::arg<m>, boost::mpl::arg<n> > > unifiers;
    };

    template<int m, int n, typename u>
    struct unify<boost::mpl::arg<m>, boost::mpl::arg<n>, u> : public unify<typename substitute<u, boost::mpl::arg<m> >::type, typename substitute<u, boost::mpl::arg<n> >::type>
    {
        private:
            typedef typename unify<typename substitute<u, boost::mpl::arg<m> >::type, typename substitute<u, boost::mpl::arg<n> >::type>::unifiers tUnifiers;

        public:
            typedef typename boost::mpl::if_
            <
                unify,
                typename boost::mpl::fold<typename unify::tUnifiers, u, boost::mpl::insert<boost::mpl::_1, boost::mpl::_2> >::type,
                boost::mpl::map<>
            >::type unifiers;
    };

    template<int n, typename u>
    struct unify<boost::mpl::arg<n>, boost::mpl::arg<n>, u> : public boost::mpl::true_
    {
            typedef u unifiers;
    };

    template<int n>
    struct unify<boost::mpl::arg<n>, boost::mpl::arg<n>, boost::mpl::map<> > : public boost::mpl::true_
    {
            typedef boost::mpl::map<> unifiers;
    };
}

#endif
