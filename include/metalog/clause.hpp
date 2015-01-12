/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _METALOG_CLAUSE_HPP_
#define _METALOG_CLAUSE_HPP_

#include "conjunction.hpp"

#include "detail/preprocessor.hpp"

#include <boost/mpl/identity.hpp>

namespace metalog
{
    template<typename consequence, typename premise = conjunction<> >
    struct clause;

    template<typename clause>
    struct consequence;

    template<typename csqc, METALOG_VARIADIC_PARAMS(METALOG_MAX_ARGS, prms)>
    struct consequence<clause<csqc, conjunction<METALOG_VARIADIC_ARGS(METALOG_MAX_ARGS, prms)> > > :
            boost::mpl::identity<csqc>
    {};

    template<typename clause>
    struct premise;

    template<typename csqc, METALOG_VARIADIC_PARAMS(METALOG_MAX_ARGS, prms)>
    struct premise<clause<csqc, conjunction<METALOG_VARIADIC_ARGS(METALOG_MAX_ARGS, prms)> > > :
            boost::mpl::identity<conjunction<METALOG_VARIADIC_ARGS(METALOG_MAX_ARGS, prms)> >
    {};
}

#endif
