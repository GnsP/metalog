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

#include <boost/mpl/bind.hpp>
#include <boost/mpl/quote.hpp>
#include <boost/mpl/identity.hpp>

#define METALOG_DEFINE_FORWARD_CALL(SEQ, FUNC, M) \
    template \
    < \
        METALOG_VARIADIC_PARAMS(METALOG_MAX_ARGS, _) \
        METALOG_TRAILING_PARAMS(BOOST_PP_SUB(M, 1), arg) \
    > \
    struct FUNC \
        < \
            SEQ<METALOG_VARIADIC_ARGS(METALOG_MAX_ARGS, _)> \
            METALOG_TRAILING_ARGS(BOOST_PP_SUB(M, 1), arg) \
        > : \
            FUNC \
            < \
                typename metalog::detail::seq::impl<SEQ<METALOG_VARIADIC_ARGS(METALOG_MAX_ARGS, _)> >::type \
                METALOG_TRAILING_ARGS(BOOST_PP_SUB(M, 1), arg) \
            > \
    {};

#define METALOG_DEFINE_ONTO_FORWARD_CALL(SEQ, FUNC, M) \
    template \
    < \
        METALOG_VARIADIC_PARAMS(METALOG_MAX_ARGS, _) \
        METALOG_TRAILING_PARAMS(BOOST_PP_SUB(M, 1), arg) \
    > \
    struct FUNC \
        < \
            SEQ<METALOG_VARIADIC_ARGS(METALOG_MAX_ARGS, _)> \
            METALOG_TRAILING_ARGS(BOOST_PP_SUB(M, 1), arg) \
        > : \
            boost::mpl::identity \
            < \
                SEQ \
                < \
                    metalog::detail::seq::seq \
                    < \
                        metalog::detail::lazy \
                        < \
                            boost::mpl::bind \
                            < \
                                BOOST_PP_CAT(boost::mpl::quote, M)<FUNC>, \
                                boost::mpl::bind \
                                < \
                                    boost::mpl::quote1<metalog::detail::seq::impl>, \
                                    SEQ<METALOG_VARIADIC_ARGS(METALOG_MAX_ARGS, _)> \
                                > \
                                METALOG_TRAILING_ARGS(BOOST_PP_SUB(M, 1), arg) \
                            > \
                        > \
                    > \
                > \
            > \
    {};

#endif
