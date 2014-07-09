/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _METALOG_RESOLVE_HPP_
#define _METALOG_RESOLVE_HPP_

#include "types.hpp"

#include <boost/mpl/map.hpp>

namespace metalog
{
    template<typename goal, typename clauses, typename u = boost::mpl::map<> >
    struct resolve :
            resolve<conjunction<goal>, clauses, u>
    {};
}

#endif
