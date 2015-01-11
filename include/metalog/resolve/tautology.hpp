/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _METALOG_RESOLVE_TAUTOLOGY_HPP_
#define _METALOG_RESOLVE_TAUTOLOGY_HPP_

#include "../preprocessor.hpp"

#include <boost/preprocessor/arithmetic/sub.hpp>

#include <boost/mpl/logical.hpp>

namespace metalog
{
    template<typename clauses, typename it, typename s>
    struct resolve<conjunction<>, clauses, it, it, s> :
            boost::mpl::true_
    {
        typedef s solution;
    };

    template<typename clauses, typename begin, typename end, typename s>
    struct resolve<conjunction<>, clauses, begin, end, s> :
            resolve<conjunction<>, clauses, end, end, s>
    {};
}

#endif
