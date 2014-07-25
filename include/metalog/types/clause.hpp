/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _METALOG_TYPES_CLAUSE_HPP_
#define _METALOG_TYPES_CLAUSE_HPP_

#include <boost/mpl/identity.hpp>

namespace metalog
{
    template<typename>
    struct consequence;

    template<typename csqc, typename prms>
    struct consequence<clause<csqc, prms> > :
            boost::mpl::identity<csqc>
    {};

    template<typename>
    struct premise;

    template<typename csqc, typename prms>
    struct premise<clause<csqc, prms> > :
            boost::mpl::identity<prms>
    {};
}

#endif
