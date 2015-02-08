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

#include "preprocessor.hpp"

#include <boost/preprocessor/empty.hpp>
#include <boost/preprocessor/control/expr_iif.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/cat.hpp>

#include <boost/mpl/identity.hpp>

#define METALOG_COLLECTION_IMPL(CONCEPT) \
    BOOST_PP_CAT(BOOST_PP_CAT(METALOG_, CONCEPT), _COLLECTION_IMPL)

#define METALOG_DEFINE_COLLECTION_ALGORITHMS(SEQ, CONCEPT) \
    BOOST_PP_CAT(BOOST_PP_CAT(METALOG_DEFINE_, CONCEPT), _COLLECTION_ALGORITHMS)(SEQ)

#define METALOG_VARIADIC_COLLECTION_SPECIALIZATION() \
    <h, METALOG_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_ARGS, 1), t)>

#define METALOG_DEFINE_COLLECTION(SEQ, CONCEPT) \
    namespace metalog \
    { \
        template<METALOG_VARIADIC_PARAMS(METALOG_MAX_ARGS, _)> \
        struct SEQ<SEQ<METALOG_VARIADIC_ARGS(METALOG_MAX_ARGS, _)> > : \
                SEQ<METALOG_VARIADIC_ARGS(METALOG_MAX_ARGS, _)> \
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
        template<typename h, METALOG_VARIADIC_PARAMS(BOOST_PP_SUB(METALOG_MAX_ARGS, 1), t)> \
        struct SEQ BOOST_PP_IIF(METALOG_NO_VARIADIC_TEMPLATES, BOOST_PP_EMPTY, METALOG_VARIADIC_COLLECTION_SPECIALIZATION)() : \
                boost::mpl::insert_range \
                < \
                    SEQ<h>, \
                    SEQ<METALOG_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_ARGS, 1), t)> \
                >::type \
        {}; \
    } \
    METALOG_DEFINE_COLLECTION_ALGORITHMS(metalog::SEQ, CONCEPT)
