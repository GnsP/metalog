/*
 * This file is part of munify, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _MUNIFY_UNIFY_HPP_
#define _MUNIFY_UNIFY_HPP_

#include "types.hpp"
#include "substitute.hpp"

#include <boost/mpl/bool.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/map.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/type_traits.hpp>

namespace munify
{
    template<typename condition, typename... unifiers>
    struct unifiable;

    template<typename condition>
    struct unifiable<condition> :
            public condition::type
    {
            typedef boost::mpl::map<> unifiers;
    };

    template<typename condition, typename hUnifiers, typename... tUnifiers>
    struct unifiable<condition, hUnifiers, tUnifiers...> :
            public unifiable<typename condition::type, tUnifiers...>
    {
        typedef typename boost::mpl::fold
        <
            typename unifiable<typename condition::type, tUnifiers...>::type,
            hUnifiers,
            boost::mpl::insert<boost::mpl::_1, boost::mpl::_2>
        >::type unifiers;
    };

    template<typename hUnifiers, typename... tUnifiers>
    struct unifiable<boost::mpl::false_, hUnifiers, tUnifiers...> :
            public unifiable<boost::mpl::false_>
    {};

    template<typename lExpr, typename rExpr, typename u = boost::mpl::map<> >
    struct unify :
            public unifiable<boost::mpl::bool_<boost::is_same<lExpr, rExpr>::value> >
    {};
}

#include "unify/equiv_transform.hpp"
#include "unify/modifiers.hpp"
#include "unify/relations.hpp"
#include "unify/vars_binding.hpp"

#endif
