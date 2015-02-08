/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _METALOG_DETAIL_COLLECTIONS_CONCEPTS_ASSOCIATIVE_HPP_
#define _METALOG_DETAIL_COLLECTIONS_CONCEPTS_ASSOCIATIVE_HPP_

#include "extensible.hpp"

#include "../algorithms.hpp"

#include <boost/mpl/map.hpp>
#include <boost/mpl/has_key.hpp>
#include <boost/mpl/count.hpp>
#include <boost/mpl/order.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/key_type.hpp>
#include <boost/mpl/value_type.hpp>
#include <boost/mpl/erase_key.hpp>

#define METALOG_ASSOCIATIVE_COLLECTION_IMPL \
    boost::mpl::map

#define METALOG_DEFINE_ASSOCIATIVE_COLLECTION_ALGORITHMS(SEQ) \
    METALOG_DEFINE_EXTENSIBLE_COLLECTION_ALGORITHMS(SEQ) \
    namespace boost \
    { \
        namespace mpl \
        { \
            METALOG_DEFINE_ALGORITHM(SEQ, has_key, 2) \
            METALOG_DEFINE_ALGORITHM(SEQ, count, 2) \
            METALOG_DEFINE_ALGORITHM(SEQ, order, 2) \
            METALOG_DEFINE_ALGORITHM(SEQ, at, 2) \
            METALOG_DEFINE_ALGORITHM(SEQ, key_type, 2) \
            METALOG_DEFINE_ALGORITHM(SEQ, value_type, 2) \
            METALOG_DEFINE_ONTO_ALGORITHM(SEQ, erase_key, 2) \
        } \
    } \

#endif
