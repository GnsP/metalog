/*
 * This file is part of munify, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _MUNIFY_UNIFIABLE_HPP_
#define _MUNIFY_UNIFIABLE_HPP_

#include "types.hpp"
#include "substitute.hpp"

#include <boost/mpl/bool.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/map.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/mpl/placeholders.hpp>

namespace munify
{
    template<typename condition, typename u>
    struct unifiable :
            public unifiable<typename boost::mpl::if_<typename condition::type, boost::mpl::true_, boost::mpl::false_>::type, u>
    {};

    template<typename u>
    struct unifiable<boost::mpl::true_, u>:
            public boost::mpl::true_
    {
            typedef typename boost::mpl::fold
            <
                u,
                boost::mpl::map<>,
                boost::mpl::insert
                <
                    boost::mpl::_1,
                    boost::mpl::pair
                    <
                        boost::mpl::first<boost::mpl::_2>,
                        boost::mpl::apply_wrap1<substitute<u>, boost::mpl::second<boost::mpl::_2> >
                    >
                >
            >::type unifiers;
    };

    template<typename u>
    struct unifiable<boost::mpl::false_, u>:
            public boost::mpl::false_
    {
            typedef boost::mpl::map<> unifiers;
    };
}

#endif
