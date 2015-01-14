/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _METALOG_DETAIL_SEQUENCES_EXTENSIBLE_ASSOCIATIVE_CONCEPT_HPP_
#define _METALOG_DETAIL_SEQUENCES_EXTENSIBLE_ASSOCIATIVE_CONCEPT_HPP_

#include "forward_call.hpp"
#include "extenders.hpp"
#include "associative_concept.hpp"

#include <boost/mpl/erase_key.hpp>

#define METALOG_IMPLEMENT_EXTENSIBLE_ASSOCIATIVE_CONCEPT(SEQ) \
    METALOG_DEFINE_EXTENDERS(SEQ) \
    METALOG_IMPLEMENT_ASSOCIATIVE_CONCEPT(SEQ) \
    namespace boost \
    { \
        namespace mpl \
        { \
            METALOG_DEFINE_LAZY_FORWARD_CALL(SEQ, erase_key, 2) \
        } \
    } \


#endif
