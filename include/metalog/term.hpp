/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _METALOG_TERM_HPP_
#define _METALOG_TERM_HPP_

#include "config.hpp"

#include "detail/preprocessor.hpp"

#include <boost/preprocessor/arithmetic/sub.hpp>

#include <boost/mpl/identity.hpp>

namespace metalog
{
    template<typename h, METALOG_VARIADIC_OPTIONAL_PARAMS(BOOST_PP_SUB(METALOG_MAX_ARGS, 1), t)>
    struct term :
            term<h, term<METALOG_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_ARGS, 1), t)> >
    {};

    template<METALOG_VARIADIC_PARAMS(METALOG_MAX_ARGS, _)>
    struct term<term<METALOG_VARIADIC_ARGS(METALOG_MAX_ARGS, _)> > :
            term<METALOG_VARIADIC_ARGS(METALOG_MAX_ARGS, _)>
    {};

    template<typename h>
    struct term<h> :
            boost::mpl::identity<term<h> >
    {};

    template<typename a, typename b>
    struct term<a, b> :
            boost::mpl::identity<term<a, b> >
    {};
}

#endif
