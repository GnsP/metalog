/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _METALOG_DETAIL_COLLECTIONS_CONCEPTS_EXTENSIBLE_HPP_
#define _METALOG_DETAIL_COLLECTIONS_CONCEPTS_EXTENSIBLE_HPP_

#include "forward.hpp"

#include "../algorithms.hpp"

#include <boost/mpl/vector.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/mpl/insert_range.hpp>
#include <boost/mpl/erase.hpp>
#include <boost/mpl/clear.hpp>
#include <boost/mpl/identity.hpp>

#define METALOG_EXTENSIBLE_COLLECTION_IMPL \
    boost::mpl::vector

#define METALOG_DEFINE_EXTENSIBLE_COLLECTION_ALGORITHMS(SEQ) \
    METALOG_DEFINE_FORWARD_COLLECTION_ALGORITHMS(SEQ) \
    namespace boost \
    { \
        namespace mpl \
        { \
            METALOG_DEFINE_ONTO_ALGORITHM(SEQ, insert, 3) \
            METALOG_DEFINE_ONTO_ALGORITHM(SEQ, insert_range, 3) \
            METALOG_DEFINE_ONTO_ALGORITHM(SEQ, erase, 3) \
            template<METALOG_VARIADIC_PARAMS(METALOG_MAX_ARGS, _)> \
            struct clear<SEQ<METALOG_VARIADIC_ARGS(METALOG_MAX_ARGS, _)> > : \
                    identity<SEQ<> > \
            {}; \
        } \
    } \

#endif
