/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _METALOG_DETAIL_SEQUENCES_IMPL_HPP_
#define _METALOG_DETAIL_SEQUENCES_IMPL_HPP_

#include "../preprocessor.hpp"
#include "../empty.hpp"

#include <boost/preprocessor/comma_if.hpp>
#include <boost/preprocessor/logical/and.hpp>

#include <boost/mpl/identity.hpp>

#define METALOG_DEFINE_IMPL_ACCESSOR(SEQ) \
    template<typename> \
    struct _impl; \
    template<typename h METALOG_TRAILING_VARIADIC_PARAMS(BOOST_PP_SUB(METALOG_MAX_ARGS, 1), t)> \
    struct _impl<SEQ<h METALOG_TRAILING_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_ARGS, 1), t)> > : \
            boost::mpl::identity<typename SEQ<h METALOG_TRAILING_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_ARGS, 1), t)>::_seq_impl> \
    {};

#define METALOG_DEFINE_IMPL(SEQ, IMPL) \
    typedef IMPL _seq_impl; \
    METALOG_DEFINE_IMPL_ACCESSOR(SEQ)

#endif
