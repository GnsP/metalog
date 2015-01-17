/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _METALOG_DETAIL_SEQUENCES_EXTENSIBLE_CONCEPT_HPP_
#define _METALOG_DETAIL_SEQUENCES_EXTENSIBLE_CONCEPT_HPP_

#include "forward_call.hpp"
#include "forward_concept.hpp"

#include "../empty.hpp"
#include "../lazy.hpp"

#include <boost/mpl/insert.hpp>
#include <boost/mpl/insert_range.hpp>
#include <boost/mpl/erase.hpp>
#include <boost/mpl/clear.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/quote.hpp>
#include <boost/mpl/bind.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/joint_view.hpp>
#include <boost/mpl/iterator_range.hpp>

#define METALOG_IMPLEMENT_EXTENSIBLE_CONCEPT(SEQ) \
    METALOG_IMPLEMENT_FORWARD_CONCEPT(SEQ) \
    namespace boost \
    { \
        namespace mpl \
        { \
            METALOG_DEFINE_LAZY_FORWARD_CALL(SEQ, insert, 3) \
            template<typename h, METALOG_VARIADIC_PARAMS(BOOST_PP_SUB(METALOG_MAX_ARGS, 1), t), typename x> \
            struct insert<SEQ<h, METALOG_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_ARGS, 1), t)>, x> : \
                insert<SEQ<h, METALOG_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_ARGS, 1), t)>, metalog::detail::_, x> \
            {}; \
            template<typename h, METALOG_VARIADIC_PARAMS(BOOST_PP_SUB(METALOG_MAX_ARGS, 1), t), typename pos, typename range> \
            struct insert_range<SEQ<h, METALOG_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_ARGS, 1), t)>, pos, range> : \
                identity \
                < \
                    SEQ \
                    < \
                        metalog::detail::lazy \
                        < \
                            bind \
                            < \
                                quote3<fold>, \
                                joint_view \
                                < \
                                    iterator_range \
                                    < \
                                        typename begin<SEQ<h, METALOG_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_ARGS, 1), t)> >::type, \
                                        pos \
                                    >, \
                                    joint_view \
                                    < \
                                        range, \
                                        iterator_range \
                                        < \
                                            pos, \
                                            typename end<SEQ<h, METALOG_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_ARGS, 1), t)> >::type \
                                        > \
                                    > \
                                >, \
                                SEQ<>, \
                                insert<_1, end<_1>, _2> \
                            > \
                        > \
                    > \
                > \
            {}; \
            METALOG_DEFINE_LAZY_FORWARD_CALL(SEQ, erase, 3) \
            template<typename h, METALOG_VARIADIC_PARAMS(BOOST_PP_SUB(METALOG_MAX_ARGS, 1), t), typename pos> \
            struct erase<SEQ<h, METALOG_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_ARGS, 1), t)>, pos> : \
                erase<SEQ<h, METALOG_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_ARGS, 1), t)>, pos, typename next<pos>::type> \
            {}; \
            template<typename h, METALOG_VARIADIC_PARAMS(BOOST_PP_SUB(METALOG_MAX_ARGS, 1), t)> \
            struct clear<SEQ<h, METALOG_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_ARGS, 1), t)> > : \
                identity<SEQ<> > \
            {}; \
        } \
    } \


#endif
