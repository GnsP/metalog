/*
 * This file is part of munify, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _MUNIFY_OCCURS_HPP_
#define _MUNIFY_OCCURS_HPP_

#include "types.hpp"
#include "substitute.hpp"

#include <boost/mpl/bool.hpp>
#include <boost/mpl/not.hpp>
#include <boost/type_traits.hpp>

namespace munify
{
    template<typename lExpr, typename rExpr>
    struct occurs :
            public boost::mpl::not_
            <
                boost::is_same
                <
                    rExpr,
                    typename substitute<boost::mpl::map<boost::mpl::pair<lExpr, void> > >::template apply<rExpr>::type
                >
            >
    {};

}

#endif
