/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _METALOG_UNIFIERS_HPP_
#define _METALOG_UNIFIERS_HPP_

#include "detail/preprocessor.hpp"
#include "detail/sequences.hpp"

#include <boost/preprocessor/arithmetic/sub.hpp>

#include <boost/mpl/map.hpp>

namespace metalog
{
    template<typename u = boost::mpl::map<>, METALOG_VARIADIC_OPTIONAL_PARAMS(BOOST_PP_SUB(METALOG_MAX_ARGS, 1), uT)>
    struct unifiers;
}

METALOG_IMPLEMENT_EXTENSIBLE_ASSOCIATIVE_CONCEPT(metalog::unifiers)

#include "unifiers/polymorphic.hpp"
#include "unifiers/variadic.hpp"

#endif
