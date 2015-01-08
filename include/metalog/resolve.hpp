/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _METALOG_RESOLVE_HPP_
#define _METALOG_RESOLVE_HPP_

#include "types.hpp"
#include "unify.hpp"
#include "join.hpp"

#include "detail/preprocessor.hpp"

#include <boost/mpl/vector.hpp>
#include <boost/mpl/map.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/end.hpp>

namespace metalog
{
    template
    <
            typename goal,
            typename clauses,
            typename begin = typename boost::mpl::begin<clauses>::type,
            typename end = typename boost::mpl::end<clauses>::type,
            typename s = boost::mpl::vector<boost::mpl::map<> >,
            METALOG_VARIADIC_PARAMS_DECLARATION(BOOST_PP_SUB(METALOG_MAX_VARIADIC_ARGS, 1), sT)
    >
    struct resolve;
}

#include "resolve/contingency.hpp"
#include "resolve/contradiction.hpp"
#include "resolve/tautology.hpp"
#include "resolve/variadic.hpp"

#endif
