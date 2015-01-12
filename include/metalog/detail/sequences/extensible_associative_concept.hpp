/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _METALOG_DETAIL_SEQUENCES_EXTENSIBLE_ASSOCIATIVE_CONCEPT_HPP_
#define _METALOG_DETAIL_SEQUENCES_EXTENSIBLE_ASSOCIATIVE_CONCEPT_HPP_

#include "forward_call.hpp"
#include "associative_concept.hpp"

#include "../empty.hpp"

#include <boost/mpl/insert.hpp>
#include <boost/mpl/erase_key.hpp>
#include <boost/mpl/erase.hpp>
#include <boost/mpl/clear.hpp>

#define METALOG_IMPLEMENT_EXTENSIBLE_ASSOCIATIVE_CONCEPT(SEQ) \
    METALOG_IMPLEMENT_ASSOCIATIVE_CONCEPT(SEQ) \
    namespace boost \
    { \
        namespace mpl \
        { \
            METALOG_DEFINE_LAZY_FORWARD_CALL(SEQ, insert, 3) \
            METALOG_DEFINE_LAZY_FORWARD_CALL(SEQ, erase_key, 2) \
            METALOG_DEFINE_LAZY_FORWARD_CALL(SEQ, erase, 3) \
            template<typename h, METALOG_VARIADIC_PARAMS(BOOST_PP_SUB(METALOG_MAX_ARGS, 1), t), typename x> \
            struct insert<SEQ<h, METALOG_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_ARGS, 1), t)>, x> : \
                insert<SEQ<h, METALOG_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_ARGS, 1), t)>, metalog::detail::_, x> \
            {}; \
            template<typename h, METALOG_VARIADIC_PARAMS(BOOST_PP_SUB(METALOG_MAX_ARGS, 1), t)> \
            struct clear<SEQ<h, METALOG_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_ARGS, 1), t)> > : \
                identity<SEQ<> > \
            {};\
        } \
    } \


#endif
