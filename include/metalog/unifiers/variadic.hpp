/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _METALOG_UNIFIERS_VARIADIC_HPP_
#define _METALOG_UNIFIERS_VARIADIC_HPP_

#include "../detail/preprocessor.hpp"

#include <boost/config.hpp>

#include <boost/preprocessor/arithmetic/sub.hpp>

#include <boost/mpl/insert_range.hpp>

namespace metalog
{
    template<typename h, METALOG_VARIADIC_PARAMS(BOOST_PP_SUB(METALOG_MAX_ARGS, 1), t)>
    struct unifiers
#ifndef BOOST_NO_CXX11_VARIADIC_TEMPLATES
            <h, METALOG_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_ARGS, 1), t)>
#endif
        :
            boost::mpl::insert_range
            <
                unifiers<h>,
                typename boost::mpl::end<unifiers<h> >::type,
                unifiers<METALOG_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_ARGS, 1), t)>
            >::type
    {};
}

#endif
