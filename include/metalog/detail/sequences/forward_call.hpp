/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _METALOG_DETAIL_SEQUENCES_FORWARD_CALL_HPP_
#define _METALOG_DETAIL_SEQUENCES_FORWARD_CALL_HPP_

#include "../preprocessor.hpp"
#include "../lazy.hpp"

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/logical/and.hpp>

#include <boost/mpl/bind.hpp>
#include <boost/mpl/quote.hpp>
#include <boost/mpl/identity.hpp>

#define METALOG_DEFINE_FORWARD_CALL(SEQ, FUNC, M) \
    template \
    < \
        typename h \
        METALOG_TRAILING_VARIADIC_PARAMS(BOOST_PP_SUB(METALOG_MAX_ARGS, 1), t) \
        METALOG_TRAILING_PARAMS(BOOST_PP_SUB(M, 1), _) \
    > \
    struct FUNC \
        < \
            SEQ<h METALOG_TRAILING_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_ARGS, 1), t)> \
            METALOG_TRAILING_ARGS(BOOST_PP_SUB(M, 1), _) \
        > : \
        FUNC \
        < \
            typename SEQ<h METALOG_TRAILING_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_ARGS, 1), t)>::template _impl \
                <SEQ<h METALOG_TRAILING_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_ARGS, 1), t)> >::type \
            METALOG_TRAILING_ARGS(BOOST_PP_SUB(M, 1), _) \
        > \
    {};

#define METALOG_DEFINE_LAZY_FORWARD_CALL(SEQ, FUNC, M) \
    template \
    < \
        typename h \
        METALOG_TRAILING_VARIADIC_PARAMS(BOOST_PP_SUB(METALOG_MAX_ARGS, 1), t) \
        METALOG_TRAILING_PARAMS(BOOST_PP_SUB(M, 1), _) \
    > \
    struct FUNC \
        < \
            SEQ<h METALOG_TRAILING_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_ARGS, 1), t)> \
            METALOG_TRAILING_ARGS(BOOST_PP_SUB(M, 1), _) \
        > : \
        boost::mpl::identity \
        < \
            SEQ \
            < \
                metalog::detail::lazy \
                < \
                    boost::mpl::bind \
                    < \
                        BOOST_PP_CAT(boost::mpl::quote, M)<FUNC>, \
                        boost::mpl::bind \
                        < \
                            boost::mpl::quote1<SEQ<h METALOG_TRAILING_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_ARGS, 1), t)>::template _impl>, \
                            SEQ<h METALOG_TRAILING_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_ARGS, 1), t)> \
                        > \
                        METALOG_TRAILING_ARGS(BOOST_PP_SUB(M, 1), _) \
                    > \
                > \
            > \
        > \
    {};

#endif
