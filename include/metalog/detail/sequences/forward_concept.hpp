/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _METALOG_DETAIL_SEQUENCES_FORWARD_CONCEPT_HPP_
#define _METALOG_DETAIL_SEQUENCES_FORWARD_CONCEPT_HPP_

#include "forward_call.hpp"

#include <boost/mpl/begin.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/front.hpp>

#define METALOG_IMPLEMENT_FORWARD_CONCEPT(SEQ) \
    namespace boost \
    { \
        namespace mpl \
        { \
            METALOG_DEFINE_FORWARD_CALL(SEQ, begin, 1) \
            METALOG_DEFINE_FORWARD_CALL(SEQ, end, 1) \
            METALOG_DEFINE_FORWARD_CALL(SEQ, size, 1) \
            METALOG_DEFINE_FORWARD_CALL(SEQ, empty, 1) \
            METALOG_DEFINE_FORWARD_CALL(SEQ, front, 1) \
        } \
    }

#endif
