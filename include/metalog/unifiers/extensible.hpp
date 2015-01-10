/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _METALOG_UNIFIERS_EXTENSIBLE_HPP_
#define _METALOG_UNIFIERS_EXTENSIBLE_HPP_

#include "../detail/lazy.hpp"
#include "../detail/empty.hpp"
#include "../detail/preprocessor.hpp"

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>

#include <boost/mpl/bind.hpp>
#include <boost/mpl/quote.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/mpl/erase_key.hpp>
#include <boost/mpl/erase.hpp>
#include <boost/mpl/clear.hpp>

namespace metalog
{
    namespace detail
    {
        template<typename>
        struct map;

        template<typename u, METALOG_VARIADIC_PARAMS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1), uT)>
        struct map<unifiers<u, METALOG_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1), uT)> > :
            boost::mpl::identity<typename unifiers<u, METALOG_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1), uT)>::map>
        {};
    }
}

#define METALOG_DEFINE_FORWARD_CALL(F, N) \
    template<typename u, METALOG_VARIADIC_PARAMS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1), uT) METALOG_TRAILING_VARIADIC_PARAMS(BOOST_PP_SUB(N, 1), _)> \
    struct F<metalog::unifiers<u, METALOG_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1), uT)> METALOG_TRAILING_VARIADIC_ARGS(BOOST_PP_SUB(N, 1), _)> : \
        identity \
        < \
            metalog::unifiers \
            < \
                metalog::detail::lazy \
                < \
                    bind \
                    < \
                        BOOST_PP_CAT(quote, N)<F>, \
                        bind<quote1<metalog::detail::map>, metalog::unifiers<u, METALOG_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1), uT)> > \
                        METALOG_TRAILING_VARIADIC_ARGS(BOOST_PP_SUB(N, 1), _) \
                    > \
                > \
            > \
        > \
    {};

namespace boost
{
    namespace mpl
    {
        METALOG_DEFINE_FORWARD_CALL(insert, 3)
        METALOG_DEFINE_FORWARD_CALL(erase_key, 2)
        METALOG_DEFINE_FORWARD_CALL(erase, 3)

        template<typename u, METALOG_VARIADIC_PARAMS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1), uT), typename x>
        struct insert<metalog::unifiers<u, METALOG_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1), uT)>, x> :
            insert<metalog::unifiers<u, METALOG_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1), uT)>, metalog::detail::_, x>
        {};

        template<typename u, METALOG_VARIADIC_PARAMS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1), uT)>
        struct clear<metalog::unifiers<u, METALOG_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1), uT)> > :
            identity<metalog::unifiers<> >
        {};
    }
}

#undef METALOG_DEFINE_FORWARD_CALL

#endif
