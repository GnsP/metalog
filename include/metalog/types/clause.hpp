/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _METALOG_TYPES_CLAUSE_HPP_
#define _METALOG_TYPES_CLAUSE_HPP_

#include "../detail/preprocessor.hpp"

#include <boost/mpl/identity.hpp>

namespace metalog
{
    template<typename>
    struct consequence;

    template<typename csqc, METALOG_VARIADIC_PARAMS(METALOG_MAX_VARIADIC_ARGS, prms)>
    struct consequence<clause<csqc, conjunction<METALOG_VARIADIC_ARGS(METALOG_MAX_VARIADIC_ARGS, prms)> > > :
            boost::mpl::identity<csqc>
    {};

    template<typename>
    struct premise;

    template<typename csqc, METALOG_VARIADIC_PARAMS(METALOG_MAX_VARIADIC_ARGS, prms)>
    struct premise<clause<csqc, conjunction<METALOG_VARIADIC_ARGS(METALOG_MAX_VARIADIC_ARGS, prms)> > > :
            boost::mpl::identity<conjunction<METALOG_VARIADIC_ARGS(METALOG_MAX_VARIADIC_ARGS, prms)> >
    {};
}

#endif
