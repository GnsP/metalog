/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _METALOG_VAR_HPP_
#define _METALOG_VAR_HPP_

#include <boost/mpl/identity.hpp>

namespace metalog
{
    template<typename n>
    struct var :
            boost::mpl::identity<var<n> >
    {};
}

#endif
