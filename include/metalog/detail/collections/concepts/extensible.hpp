/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _METALOG_DETAIL_COLLECTIONS_CONCEPTS_EXTENSIBLE_HPP_
#define _METALOG_DETAIL_COLLECTIONS_CONCEPTS_EXTENSIBLE_HPP_

#include "forward.hpp"

#include "../algorithms.hpp"

#include "../../lazy.hpp"

#include <boost/mpl/vector.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/mpl/erase.hpp>
#include <boost/mpl/clear.hpp>
#include <boost/mpl/insert_range.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/quote.hpp>
#include <boost/mpl/bind.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/joint_view.hpp>
#include <boost/mpl/iterator_range.hpp>

#define METALOG_EXTENSIBLE_COLLECTION_IMPL \
    boost::mpl::vector

#define METALOG_DEFINE_EXTENSIBLE_COLLECTION_ALGORITHMS(SEQ) \
    METALOG_DEFINE_FORWARD_COLLECTION_ALGORITHMS(SEQ) \
    namespace boost \
    { \
        namespace mpl \
        { \
            METALOG_DEFINE_ONTO_ALGORITHM(SEQ, insert, 3) \
            METALOG_DEFINE_ONTO_ALGORITHM(SEQ, erase, 3) \
            template<METALOG_VARIADIC_PARAMS(METALOG_MAX_ARGS, _)> \
            struct clear<SEQ<METALOG_VARIADIC_ARGS(METALOG_MAX_ARGS, _)> > : \
                    identity<SEQ<> > \
            {}; \
            template<METALOG_VARIADIC_PARAMS(METALOG_MAX_ARGS, _), typename pos, typename range> \
            struct insert_range<SEQ<METALOG_VARIADIC_ARGS(METALOG_MAX_ARGS, _)>, pos, range> : \
                    identity \
                    < \
                        SEQ \
                        < \
                            metalog::detail::collections::seq \
                            < \
                                metalog::detail::lazy \
                                < \
                                    bind3 \
                                    < \
                                        quote3<fold>, \
                                        joint_view \
                                        < \
                                            iterator_range \
                                            < \
                                                typename begin<SEQ<METALOG_VARIADIC_ARGS(METALOG_MAX_ARGS, _)> >::type, \
                                                pos \
                                            >, \
                                            joint_view \
                                            < \
                                                range, \
                                                iterator_range \
                                                < \
                                                    pos, \
                                                    typename end<SEQ<METALOG_VARIADIC_ARGS(METALOG_MAX_ARGS, _)> >::type \
                                                > \
                                            > \
                                        >, \
                                        SEQ<>, \
                                        insert<boost::mpl::_1, end<boost::mpl::_1>, boost::mpl::_2> \
                                    > \
                                > \
                            > \
                        > \
                    > \
            {}; \
            template<METALOG_VARIADIC_PARAMS(METALOG_MAX_ARGS, _), typename range> \
            struct insert_range<SEQ<METALOG_VARIADIC_ARGS(METALOG_MAX_ARGS, _)>, range> : \
                    insert_range \
                    < \
                        SEQ<METALOG_VARIADIC_ARGS(METALOG_MAX_ARGS, _)>, \
                        typename boost::mpl::end<SEQ<METALOG_VARIADIC_ARGS(METALOG_MAX_ARGS, _)> >::type, \
                        range \
                    > \
            {}; \
        } \
    } \

#endif
