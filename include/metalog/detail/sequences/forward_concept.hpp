/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _METALOG_DETAIL_SEQUENCES_FORWARD_CONCEPT_HPP_
#define _METALOG_DETAIL_SEQUENCES_FORWARD_CONCEPT_HPP_

#include "algorithms.hpp"

#include <boost/mpl/begin.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/copy.hpp>
#include <boost/mpl/copy_if.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/replace.hpp>
#include <boost/mpl/replace_if.hpp>
#include <boost/mpl/remove.hpp>
#include <boost/mpl/remove_if.hpp>
#include <boost/mpl/unique.hpp>
#include <boost/mpl/sort.hpp>
#include <boost/mpl/reverse.hpp>

#define METALOG_IMPLEMENT_FORWARD_CONCEPT(SEQ) \
    namespace boost \
    { \
        namespace mpl \
        { \
            METALOG_DEFINE_ALGORITHM(SEQ, begin, 1) \
            METALOG_DEFINE_ALGORITHM(SEQ, end, 1) \
            METALOG_DEFINE_ALGORITHM(SEQ, size, 1) \
            METALOG_DEFINE_ALGORITHM(SEQ, empty, 1) \
            METALOG_DEFINE_ALGORITHM(SEQ, front, 1) \
            METALOG_DEFINE_ONTO_ALGORITHM(SEQ, copy, 2) \
            METALOG_DEFINE_ONTO_ALGORITHM(SEQ, copy_if, 3) \
            METALOG_DEFINE_ONTO_ALGORITHM(SEQ, transform, 4) \
            METALOG_DEFINE_ONTO_ALGORITHM(SEQ, replace, 4) \
            METALOG_DEFINE_ONTO_ALGORITHM(SEQ, replace_if, 4) \
            METALOG_DEFINE_ONTO_ALGORITHM(SEQ, remove, 3) \
            METALOG_DEFINE_ONTO_ALGORITHM(SEQ, remove_if, 3) \
            METALOG_DEFINE_ONTO_ALGORITHM(SEQ, unique, 3) \
            METALOG_DEFINE_ONTO_ALGORITHM(SEQ, sort, 3) \
            METALOG_DEFINE_ONTO_ALGORITHM(SEQ, reverse, 2) \
            METALOG_DEFINE_ONTO_ALGORITHM(SEQ, reverse_copy, 2) \
            METALOG_DEFINE_ONTO_ALGORITHM(SEQ, reverse_copy_if, 3) \
            METALOG_DEFINE_ONTO_ALGORITHM(SEQ, reverse_transform, 4) \
            METALOG_DEFINE_ONTO_ALGORITHM(SEQ, reverse_replace, 4) \
            METALOG_DEFINE_ONTO_ALGORITHM(SEQ, reverse_replace_if, 4) \
            METALOG_DEFINE_ONTO_ALGORITHM(SEQ, reverse_remove, 3) \
            METALOG_DEFINE_ONTO_ALGORITHM(SEQ, reverse_remove_if, 3) \
            METALOG_DEFINE_ONTO_ALGORITHM(SEQ, reverse_unique, 3) \
        } \
    }

#endif
