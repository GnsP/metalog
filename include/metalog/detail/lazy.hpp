/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _METALOG_DETAIL_LAZY_HPP_
#define _METALOG_DETAIL_LAZY_HPP_

#include "preprocessor.hpp"

#include <boost/preprocessor/repetition/repeat_from_to.hpp>

#include <boost/mpl/bind.hpp>
#include <boost/mpl/apply_wrap.hpp>

#define METALOG_DEFINE_LAZY_BIND(N) \
    template<typename f METALOG_TRAILING_VARIADIC_PARAMS(N, arg)> \
    struct lazy<boost::mpl::bind<f METALOG_TRAILING_VARIADIC_ARGS(N, arg)> > : \
            boost::mpl::apply_wrap0<boost::mpl::bind<f METALOG_TRAILING_VARIADIC_ARGS(N, arg)> > \
    {};

#define METALOG_FORWARD_DEFINE_LAZY_BIND(Z, N, DATA) \
    METALOG_DEFINE_LAZY_BIND(N)

namespace metalog
{
    namespace detail
    {
        template<typename f>
        struct lazy;

#ifdef BOOST_NO_CXX11_VARIADIC_TEMPLATES
        BOOST_PP_REPEAT_FROM_TO(0, BOOST_MPL_LIMIT_METAFUNCTION_ARITY, METALOG_FORWARD_DEFINE_LAZY_BIND, _)
#endif

        METALOG_DEFINE_LAZY_BIND(BOOST_MPL_LIMIT_METAFUNCTION_ARITY)
    }
}

#undef METALOG_DEFINE_LAZY_BIND
#undef METALOG_FORWARD_DEFINE_LAZY_BIND

#endif
