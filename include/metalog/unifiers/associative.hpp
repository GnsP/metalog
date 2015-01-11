/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _METALOG_UNIFIERS_ASSOCIATIVE_HPP_
#define _METALOG_UNIFIERS_ASSOCIATIVE_HPP_

#include "../preprocessor.hpp"

#include <boost/preprocessor/arithmetic/sub.hpp>

#include <boost/mpl/begin.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/has_key.hpp>
#include <boost/mpl/count.hpp>
#include <boost/mpl/order.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/key_type.hpp>
#include <boost/mpl/value_type.hpp>

#define METALOG_DEFINE_FORWARD_CALL(F, N) \
    template<typename u, METALOG_VARIADIC_PARAMS(BOOST_PP_SUB(METALOG_MAX_ARGS, 1), uT) METALOG_TRAILING_VARIADIC_PARAMS(BOOST_PP_SUB(N, 1), _)> \
    struct F<metalog::unifiers<u, METALOG_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_ARGS, 1), uT)> METALOG_TRAILING_VARIADIC_ARGS(BOOST_PP_SUB(N, 1), _)> : \
        F \
        < \
            typename metalog::unifiers<u, METALOG_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_ARGS, 1), uT)>::map \
            METALOG_TRAILING_VARIADIC_ARGS(BOOST_PP_SUB(N, 1), _) \
        > \
    {};

namespace boost
{
    namespace mpl
    {
        METALOG_DEFINE_FORWARD_CALL(begin, 1)
        METALOG_DEFINE_FORWARD_CALL(end, 1)
        METALOG_DEFINE_FORWARD_CALL(size, 1)
        METALOG_DEFINE_FORWARD_CALL(empty, 1)
        METALOG_DEFINE_FORWARD_CALL(front, 1)
        METALOG_DEFINE_FORWARD_CALL(has_key, 2)
        METALOG_DEFINE_FORWARD_CALL(count, 2)
        METALOG_DEFINE_FORWARD_CALL(order, 2)
        METALOG_DEFINE_FORWARD_CALL(at, 2)
        METALOG_DEFINE_FORWARD_CALL(key_type, 2)
        METALOG_DEFINE_FORWARD_CALL(value_type, 2)
    }
}

#undef METALOG_DEFINE_FORWARD_CALL

#endif
