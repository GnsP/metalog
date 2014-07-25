/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _METALOG_TYPES_VAR_HPP_
#define _METALOG_TYPES_VAR_HPP_

#include "../detail/empty.hpp"

#include <boost/mpl/identity.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/has_key.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/mpl/erase_key.hpp>

namespace metalog
{
    template<typename unifiers, typename key>
    struct bond;

    template<typename unifiers, typename n>
    struct bond<unifiers, var<n> > :
            boost::mpl::has_key<unifiers, var<n> >
    {};

    template<typename unifiers, typename key, typename value>
    struct bind;

    template<typename unifiers, typename key>
    struct bind<unifiers, key, key>;

    template<typename unifiers, typename n, typename value>
    struct bind<unifiers, var<n>, value> :
            boost::mpl::if_
            <
                bond<unifiers, var<n> >,
                detail::_,
                boost::mpl::insert<unifiers, boost::mpl::pair<var<n>, value> >
            >::type
    {};

    template<typename unifiers, typename key>
    struct unbind;

    template<typename unifiers, typename n>
    struct unbind<unifiers, var<n> > :
            boost::mpl::if_
            <
                bond<unifiers, var<n> >,
                boost::mpl::erase_key<unifiers, var<n> >,
                boost::mpl::identity<unifiers>
            >::type
    {};

    template<typename unifiers, typename key>
    struct lookup;

    template<typename unifiers, typename n>
    struct lookup<unifiers, var<n> > :
            boost::mpl::if_
            <
                bond<unifiers, var<n> >,
                boost::mpl::at<unifiers, var<n> >,
                boost::mpl::identity<var<n> >
            >::type
    {};
}

#endif
