/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _METALOG_DETAIL_SEQUENCES_EXTENDERS_HPP_
#define _METALOG_DETAIL_SEQUENCES_EXTENDERS_HPP_

#include "forward_call.hpp"
#include "forward_call.hpp"

#include "../empty.hpp"

#include <boost/mpl/insert.hpp>
#include <boost/mpl/erase.hpp>
#include <boost/mpl/clear.hpp>
#include <boost/mpl/next.hpp>

#define METALOG_DEFINE_EXTENDERS(SEQ) \
    namespace boost \
    { \
        namespace mpl \
        { \
            METALOG_DEFINE_LAZY_FORWARD_CALL(SEQ, insert, 3) \
            template<typename h, METALOG_VARIADIC_PARAMS(BOOST_PP_SUB(METALOG_MAX_ARGS, 1), t), typename x> \
            struct insert<SEQ<h, METALOG_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_ARGS, 1), t)>, x> : \
                insert<SEQ<h, METALOG_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_ARGS, 1), t)>, metalog::detail::_, x> \
            {}; \
            METALOG_DEFINE_LAZY_FORWARD_CALL(SEQ, erase, 3) \
            template<typename h, METALOG_VARIADIC_PARAMS(BOOST_PP_SUB(METALOG_MAX_ARGS, 1), t), typename pos> \
            struct erase<SEQ<h, METALOG_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_ARGS, 1), t)>, pos> : \
                erase<SEQ<h, METALOG_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_ARGS, 1), t)>, pos, typename boost::mpl::next<pos>::type> \
            {}; \
            METALOG_DEFINE_LAZY_FORWARD_CALL(SEQ, clear, 1) \
        } \
    } \


#endif
