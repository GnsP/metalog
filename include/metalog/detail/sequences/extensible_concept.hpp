/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _METALOG_DETAIL_SEQUENCES_EXTENSIBLE_CONCEPT_HPP_
#define _METALOG_DETAIL_SEQUENCES_EXTENSIBLE_CONCEPT_HPP_

#include "forward_call.hpp"
#include "extenders.hpp"
#include "forward_concept.hpp"

#include "../empty.hpp"

#include <boost/mpl/insert.hpp>
#include <boost/mpl/insert_range.hpp>
#include <boost/mpl/erase.hpp>
#include <boost/mpl/clear.hpp>
#include <boost/mpl/next.hpp>

#define METALOG_IMPLEMENT_EXTENSIBLE_CONCEPT(SEQ) \
    METALOG_DEFINE_EXTENDERS(SEQ) \
    METALOG_IMPLEMENT_FORWARD_CONCEPT(SEQ) \
    namespace boost \
    { \
        namespace mpl \
        { \
            METALOG_DEFINE_LAZY_FORWARD_CALL(SEQ, insert_range, 3) \
        } \
    } \


#endif
