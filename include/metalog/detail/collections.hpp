/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#include "collections/impl.hpp"
#include "collections/algorithms.hpp"
#include "collections/concepts/forward.hpp"
#include "collections/concepts/extensible.hpp"
#include "collections/concepts/associative.hpp"

#include "lazy.hpp"
#include "preprocessor.hpp"

#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/cat.hpp>

#include <boost/mpl/vector.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/quote.hpp>
#include <boost/mpl/bind.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/insert.hpp>

#define METALOG_COLLECTION_IMPL(CONCEPT) \
    BOOST_PP_CAT(BOOST_PP_CAT(METALOG_, CONCEPT), _COLLECTION_IMPL)

#define METALOG_DEFINE_COLLECTION_ALGORITHMS(SEQ, CONCEPT) \
    BOOST_PP_CAT(BOOST_PP_CAT(METALOG_DEFINE_, CONCEPT), _COLLECTION_ALGORITHMS)(SEQ)

#define METALOG_DEFINE_COLLECTION(SEQ, CONCEPT) \
    namespace metalog \
    { \
        template<METALOG_VARIADIC_PARAMS(METALOG_MAX_ARGS, _)> \
        struct SEQ : \
            SEQ<METALOG_WRAP_EACH_VARIADIC_ARG(METALOG_MAX_ARGS, _, SEQ)> \
        {}; \
        template<typename seq> \
        struct SEQ<detail::collections::seq<seq> > : \
                boost::mpl::identity<SEQ<detail::collections::seq<seq> > > \
        { \
            typedef detail::collections::seq<seq> impl; \
        }; \
        template<> \
        struct SEQ<> : \
                SEQ<detail::collections::seq<METALOG_COLLECTION_IMPL(CONCEPT)<> > > \
        {}; \
        template<typename item> \
        struct SEQ<item> : \
                SEQ<detail::collections::seq<METALOG_COLLECTION_IMPL(CONCEPT)<item> > > \
        {}; \
        template<METALOG_VARIADIC_PARAMS(METALOG_MAX_ARGS, h)> \
        struct SEQ<SEQ<METALOG_VARIADIC_ARGS(METALOG_MAX_ARGS, h)> > : \
                SEQ<METALOG_VARIADIC_ARGS(METALOG_MAX_ARGS, h)> \
        {}; \
        template \
        < \
            METALOG_VARIADIC_PARAMS(METALOG_MAX_ARGS, h) \
            METALOG_TRAILING_VARIADIC_PARAMS(BOOST_PP_SUB(METALOG_MAX_ARGS, 1), t) \
        > \
        struct SEQ \
        < \
            SEQ<METALOG_VARIADIC_ARGS(METALOG_MAX_ARGS, h)> \
            METALOG_TRAILING_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_ARGS, 1), t) \
        > : \
                SEQ \
                < \
                    detail::collections::seq \
                    < \
                        detail::lazy \
                        < \
                            boost::mpl::bind3 \
                            < \
                                boost::mpl::quote3<boost::mpl::fold>, \
                                boost::mpl::vector \
                                < \
                                    METALOG_WRAP_EACH_VARIADIC_ARG(BOOST_PP_SUB(METALOG_MAX_ARGS, 1), t, SEQ) \
                                >, \
                                boost::mpl::bind1 \
                                < \
                                    boost::mpl::quote1<metalog::detail::collections::impl>, \
                                    SEQ<METALOG_VARIADIC_ARGS(METALOG_MAX_ARGS, h)> \
                                >, \
                                boost::mpl::insert_range<boost::mpl::_1, boost::mpl::end<boost::mpl::_1>, boost::mpl::_2> \
                            > \
                        > \
                    > \
                > \
        {}; \
    } \
    METALOG_DEFINE_COLLECTION_ALGORITHMS(metalog::SEQ, CONCEPT)
