/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _METALOG_DETAIL_SEQUENCES_ASSOCIATIVE_CONCEPT_HPP_
#define _METALOG_DETAIL_SEQUENCES_ASSOCIATIVE_CONCEPT_HPP_

#include "forward_call.hpp"
#include "forward_concept.hpp"

#include <boost/mpl/has_key.hpp>
#include <boost/mpl/count.hpp>
#include <boost/mpl/order.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/key_type.hpp>
#include <boost/mpl/value_type.hpp>

#define METALOG_IMPLEMENT_ASSOCIATIVE_CONCEPT(SEQ) \
    METALOG_IMPLEMENT_FORWARD_CONCEPT(SEQ) \
    namespace boost \
    { \
        namespace mpl \
        { \
            METALOG_DEFINE_FORWARD_CALL(SEQ, has_key, 2) \
            METALOG_DEFINE_FORWARD_CALL(SEQ, count, 2) \
            METALOG_DEFINE_FORWARD_CALL(SEQ, order, 2) \
            METALOG_DEFINE_FORWARD_CALL(SEQ, at, 2) \
            METALOG_DEFINE_FORWARD_CALL(SEQ, key_type, 2) \
            METALOG_DEFINE_FORWARD_CALL(SEQ, value_type, 2) \
        } \
    }

#endif
