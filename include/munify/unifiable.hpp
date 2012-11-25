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
#include <boost/mpl/map.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/insert.hpp>

namespace munify
{
    template<typename condition, typename u>
    struct unifiable :
            public unifiable<typename boost::mpl::if_<typename condition::type, boost::mpl::true_, boost::mpl::false_>::type, u>
    {};

    template<bool b, typename u>
    struct unifiable<boost::mpl::bool_<b>, u>:
            public boost::mpl::bool_<b>
    {
            typedef u unifiers;
    };
}

#endif
