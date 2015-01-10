/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _METALOG_TYPES_HPP_
#define _METALOG_TYPES_HPP_

#include "detail/preprocessor.hpp"

#include <boost/preprocessor/arithmetic/sub.hpp>

namespace metalog
{
    template
    <
            typename lExpr, typename rExpr, typename u,
            METALOG_VARIADIC_PARAMS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1), uT)
    >
    struct unify;

    template<typename u, METALOG_VARIADIC_PARAMS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1), uT)>
    struct unifiers;

    /**
     * An atom is considered to be a constant for the purpose of unification.
     * The unification of atom<A> with atom<B> succeeds iff A is literally equal to B,
     * regardless of variable substitutions.
     */
    template<typename>
    struct atom;

    template<typename>
    struct var;

    template<typename, METALOG_VARIADIC_PARAMS_DECLARATION(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1), _)>
    struct term;

    template
    <
            typename goal, typename clauses, typename begin, typename end, typename s,
            METALOG_VARIADIC_PARAMS(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1), sT)
    >
    struct resolve;

    template<METALOG_VARIADIC_PARAMS_DECLARATION(METALOG_MAX_VARIADIC_ARGS, _)>
    struct conjunction;

    template<typename premise, typename consequence = conjunction<> >
    struct clause;
}

#include "types/clause.hpp"
#include "types/resolve.hpp"

#endif
