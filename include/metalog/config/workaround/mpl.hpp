/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _METALOG_CONFIG_WORKAROUND_MPL_HPP_
#define _METALOG_CONFIG_WORKAROUND_MPL_HPP_

#include <boost/mpl/aux_/preprocessor/range.hpp>

#include <boost/preprocessor/seq/subseq.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/arithmetic/add.hpp>

#undef BOOST_MPL_PP_RANGE

#define BOOST_MPL_PP_RANGE_ITEM(z,n,_) (n)

#define BOOST_MPL_PP_RANGE(first, length) \
    BOOST_PP_SEQ_SUBSEQ( \
        BOOST_PP_REPEAT(BOOST_PP_ADD(first,length),BOOST_MPL_PP_RANGE_ITEM,_), \
        first, length \
    )

#endif
