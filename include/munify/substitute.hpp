/*
 * This file is part of munify, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _MUNIFY_SUBSTITUTE_HPP_
#define _MUNIFY_SUBSTITUTE_HPP_

#include "unwrap_sequence.hpp"

#include <boost/mpl/arg.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/map.hpp>
#include <boost/mpl/list.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/has_key.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>

namespace munify
{
    template<typename unifiers, typename expr>
    struct substitute
    {
            typedef expr type;
    };

    template<typename unifiers, int n>
    struct substitute<unifiers, boost::mpl::arg<n> >
    {
//            boost bug #3982
//            typedef typename boost::mpl::at<unifiers, boost::mpl::arg<n>, boost::mpl::arg<n> >::type type;

            typedef typename boost::mpl::eval_if
            <
                typename boost::mpl::has_key<unifiers, boost::mpl::arg<n> >::type,
                boost::mpl::at<unifiers, boost::mpl::arg<n> >,
                boost::mpl::identity<boost::mpl::arg<n> >
            >::type type;
    };

    template<typename unifiers, template<typename...> class rel, typename... args>
    struct substitute<unifiers, rel<args...> >
    {
            typedef typename unwrap_sequence
            <
                typename boost::mpl::transform<boost::mpl::list<args...>, substitute<unifiers, boost::mpl::_1> >::type,
                rel
            >::type type;
    };
}

#endif
