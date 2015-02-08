/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _METALOG_DETAIL_COLLECTIONS_ALGORITHMS_HPP_
#define _METALOG_DETAIL_COLLECTIONS_ALGORITHMS_HPP_

#include "impl.hpp"

#include "../preprocessor.hpp"
#include "../lazy.hpp"

#include <boost/preprocessor/cat.hpp>

#include <boost/mpl/bind.hpp>
#include <boost/mpl/quote.hpp>
#include <boost/mpl/identity.hpp>

#define METALOG_DEFINE_ALGORITHM(SEQ, FUNC, ARITY) \
    template \
    < \
        METALOG_VARIADIC_PARAMS(METALOG_MAX_ARGS, _) \
        METALOG_TRAILING_PARAMS(BOOST_PP_SUB(ARITY, 1), arg) \
    > \
    struct FUNC \
        < \
            SEQ<METALOG_VARIADIC_ARGS(METALOG_MAX_ARGS, _)> \
            METALOG_TRAILING_ARGS(BOOST_PP_SUB(ARITY, 1), arg) \
        > : \
            FUNC \
            < \
                typename metalog::detail::collections::impl<SEQ<METALOG_VARIADIC_ARGS(METALOG_MAX_ARGS, _)> >::type \
                METALOG_TRAILING_ARGS(BOOST_PP_SUB(ARITY, 1), arg) \
            > \
    {};

#define METALOG_DEFINE_ONTO_ALGORITHM(SEQ, FUNC, ARITY) \
    template \
    < \
        METALOG_VARIADIC_PARAMS(METALOG_MAX_ARGS, _) \
        METALOG_TRAILING_PARAMS(BOOST_PP_SUB(ARITY, 1), arg) \
    > \
    struct FUNC \
        < \
            SEQ<METALOG_VARIADIC_ARGS(METALOG_MAX_ARGS, _)> \
            METALOG_TRAILING_ARGS(BOOST_PP_SUB(ARITY, 1), arg) \
        > : \
            boost::mpl::identity \
            < \
                SEQ \
                < \
                    metalog::detail::collections::seq \
                    < \
                        metalog::detail::lazy \
                        < \
                            BOOST_PP_CAT(boost::mpl::bind, ARITY) \
                            < \
                                BOOST_PP_CAT(boost::mpl::quote, ARITY)<FUNC>, \
                                boost::mpl::bind1 \
                                < \
                                    boost::mpl::quote1<metalog::detail::collections::impl>, \
                                    SEQ<METALOG_VARIADIC_ARGS(METALOG_MAX_ARGS, _)> \
                                > \
                                METALOG_TRAILING_ARGS(BOOST_PP_SUB(ARITY, 1), arg) \
                            > \
                        > \
                    > \
                > \
            > \
    {};


#endif
