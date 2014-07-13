/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _METALOG_RESOLVE_HPP_
#define _METALOG_RESOLVE_HPP_

#include "types.hpp"
#include "unify.hpp"

#include "detail/preprocessor.hpp"

#include <boost/mpl/bool.hpp>
#include <boost/mpl/size.hpp>
#include <boost/type_traits.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/map.hpp>
#include <boost/mpl/set.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/copy.hpp>
#include <boost/mpl/back_inserter.hpp>

namespace metalog
{
    template
    <
            typename goal,
            typename clauses,
            typename begin = typename boost::mpl::begin<clauses>::type,
            typename end = typename boost::mpl::end<clauses>::type,
            typename solution = boost::mpl::vector<boost::mpl::map<> >
    >
    struct resolve :
            resolve<conjunction<goal>, clauses, begin, end, solution>
    {};

    template<typename hG, METALOG_VARIADIC_PARAMS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1), tG), typename clauses, typename it, typename s>
    struct resolve<conjunction<hG METALOG_TRAILING_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1), tG)>, clauses, it, it, s> :
            boost::mpl::bool_<(boost::mpl::size<s>::value > 1)>
    {
        typedef typename boost::mpl::pop_front<s>::type solution;
    };

    template<typename clauses, typename it, typename s>
    struct resolve<conjunction<METALOG_VARIADIC_EMPTY_ARGS(METALOG_MAX_VARIADIC_ARGS)>, clauses, it, it, s> :
            boost::mpl::true_
    {
        typedef s solution;
    };

    template<typename clauses, typename begin, typename end, typename solution>
    struct resolve<conjunction<METALOG_VARIADIC_EMPTY_ARGS(METALOG_MAX_VARIADIC_ARGS)>, clauses, begin, end, solution> :
            resolve<conjunction<>, clauses, end, end, solution>
    {};


    template
    <
            typename hG,
            METALOG_VARIADIC_PARAMS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1), tG),
            typename clauses,
            typename it,
            typename end,
            typename solution
    >
    struct resolve
            <
                conjunction<hG METALOG_TRAILING_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1), tG)>,
                clauses,
                it,
                end,
                solution
            > :
            resolve
            <
                conjunction<hG METALOG_TRAILING_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1), tG)>,
                clauses,
                typename boost::mpl::next<it>::type,
                end,
                typename boost::mpl::if_
                <
                    unify<hG, typename consequence<typename boost::mpl::deref<it>::type>::type, typename boost::mpl::front<solution>::type>,
                    typename boost::mpl::copy
                    <
                        typename resolve
                        <
                            typename join
                            <
                                typename premise<typename boost::mpl::deref<it>::type>::type,
                                conjunction<METALOG_VARIADIC_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1), tG)>
                            >::type,
                            clauses,
                            typename boost::mpl::begin<clauses>::type,
                            end,
                            typename boost::mpl::push_front
                            <
                                typename boost::mpl::pop_front<solution>::type,
                                typename unify<hG, typename consequence<typename boost::mpl::deref<it>::type>::type, typename boost::mpl::front<solution>::type>::unifiers
                            >::type
                        >::solution,
                        boost::mpl::back_inserter<solution>
                    >::type,
                    solution
                >::type
            >
    {};
}

#endif