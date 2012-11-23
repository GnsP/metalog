/*
 * This file is part of munify, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _MUNIFY_SUBSTITUTE_HPP_
#define _MUNIFY_SUBSTITUTE_HPP_

#include <boost/mpl/arg.hpp>
#include <boost/mpl/map.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/has_key.hpp>
#include <boost/mpl/eval_if.hpp>

namespace munify
{
    template<typename unifiers>
    struct substitute
    {
            template<typename expr>
            struct apply
            {
                    typedef expr type;
            };

            template<int n>
            struct apply<boost::mpl::arg<n> >
            {
                    //boost bug #3982
                    //typedef typename boost::mpl::at<unifiers, boost::mpl::arg<n>, boost::mpl::arg<n> >::type type;

                    typedef typename boost::mpl::eval_if
                    <
                        boost::mpl::has_key<unifiers, boost::mpl::arg<n> >,
                        boost::mpl::at<unifiers, boost::mpl::arg<n> >,
                        boost::mpl::identity<boost::mpl::arg<n> >
                    >::type type;
            };

            template<template<typename, typename...> class rel, typename... expr>
            struct apply<rel<expr...> >
            {
                    typedef rel<typename substitute::template apply<expr>::type...> type;
            };
    };
}

#endif
