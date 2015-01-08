/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _METALOG_RESOLVE_CONTINGENCY_HPP_
#define _METALOG_RESOLVE_CONTINGENCY_HPP_

#include "../types.hpp"

#include "../detail/preprocessor.hpp"

#include <boost/preprocessor/arithmetic/sub.hpp>

#include <boost/mpl/vector.hpp>
#include <boost/mpl/map.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>

namespace metalog
{
    namespace detail
    {
        template<typename unification, typename goal, typename clauses, typename begin, typename end>
        struct recurse_if :
                boost::mpl::eval_if
                <
                    unification,
                    solution<resolve<goal, clauses, begin, end, boost::mpl::vector<typename unifiers<unification>::type> > >,
                    boost::mpl::identity<boost::mpl::vector<> >
                >::type
        {};
    }

    template<typename goal, typename clauses, typename begin, typename end, typename s>
    struct resolve<goal, clauses, begin, end, s> :
            resolve<conjunction<goal>, clauses, begin, end, s>
    {};


    template
    <
            typename hG, METALOG_VARIADIC_PARAMS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1), tG),
            typename clauses, typename it, typename end, typename s
    >
    struct resolve
            <
                conjunction<hG METALOG_TRAILING_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1), tG)>,
                clauses, it, end, s
            > :
            resolve
            <
                conjunction<hG METALOG_TRAILING_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1), tG)>,
                clauses,
                typename boost::mpl::next<it>::type,
                end,
                s,
                typename detail::recurse_if
                <
                    unify<hG, typename consequence<typename boost::mpl::deref<it>::type>::type, typename boost::mpl::front<s>::type>,
                    typename join
                    <
                        typename premise<typename boost::mpl::deref<it>::type>::type,
                        conjunction<METALOG_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1), tG)>
                    >::type,
                    clauses,
                    typename boost::mpl::begin<clauses>::type,
                    end
                >::type
            >
    {};
}

#endif
