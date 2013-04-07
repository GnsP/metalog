/*
 * This file is part of munify, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _MUNIFY_SUBSTITUTE_HPP_
#define _MUNIFY_SUBSTITUTE_HPP_

#include "types.hpp"

#include <boost/mpl/map.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/has_key.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/type_traits.hpp>

namespace munify
{
    template<typename unifiers>
    struct substitute
    {
        template<typename expr>
        struct apply :
                boost::mpl::identity<expr>
        {};

        template<int n>
        class apply<var<n> >
        {
        private:
            //boost bug #3982
            //typedef typename boost::mpl::at<unifiers, var<n>, var<n> >::type lookup;

            typedef typename boost::mpl::eval_if
            <
                boost::mpl::has_key<unifiers, var<n> >,
                boost::mpl::at<unifiers, var<n> >,
                boost::mpl::identity<var<n> >
            >::type lookup;

        public:
            //recurse until there is nothing left to substitute
            typedef typename boost::mpl::eval_if
            <
                boost::is_same<var<n>, lookup>,
                boost::mpl::identity<lookup>,
                boost::mpl::apply_wrap1<substitute<unifiers>, lookup>
            >::type type;
        };

        template<template<typename...> class term, typename hExpr, typename... tExpr>
        struct apply<term<hExpr, tExpr...> > :
                boost::mpl::identity
                <
                    term
                    <
                        typename boost::mpl::apply_wrap1<substitute<unifiers>, hExpr>::type,
                        typename boost::mpl::apply_wrap1<substitute<unifiers>, tExpr>::type...
                    >
                >
        {};

        template<typename expr>
        struct apply<atom<expr> > :
                boost::mpl::identity<atom<expr> >
        {};
    };
}

#endif
