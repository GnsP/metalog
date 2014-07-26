/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _METALOG_UNIFY_LAZY_HPP_
#define _METALOG_UNIFY_LAZY_HPP_

#include "../detail/lazy.hpp"
#include "../detail/preprocessor.hpp"

#include <boost/preprocessor/arithmetic/sub.hpp>

namespace metalog
{
    template<typename lExpr, typename rExpr, typename u>
    struct unify<detail::lazy<lExpr>, rExpr, u METALOG_TRAILING_VARIADIC_EMPTY_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1))>:
            unify<typename boost::mpl::apply_wrap0<lExpr>::type, rExpr, u>
    {};

    template<typename lExpr, typename rExpr, typename u>
    struct unify<lExpr, detail::lazy<rExpr>, u METALOG_TRAILING_VARIADIC_EMPTY_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1))>:
            unify<lExpr, typename boost::mpl::apply_wrap0<rExpr>::type, u>
    {};

    template<typename lExpr, typename rExpr, typename u>
    struct unify<detail::lazy<lExpr>, detail::lazy<rExpr>, u METALOG_TRAILING_VARIADIC_EMPTY_ARGS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1))>:
            unify<typename boost::mpl::apply_wrap0<lExpr>::type, typename boost::mpl::apply_wrap0<rExpr>::type, u>
    {};
}

#endif
