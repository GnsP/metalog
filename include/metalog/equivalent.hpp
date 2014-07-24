/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _METALOG_EQUIVALENT_HPP_
#define _METALOG_EQUIVALENT_HPP_

#include "types.hpp"

#include <boost/type_traits.hpp>

#include <boost/mpl/logical.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/placeholders.hpp>

namespace metalog
{
    template<typename lUnifiers, typename rUnifiers>
    struct equivalent :
            boost::mpl::and_
            <
                boost::mpl::equal_to<boost::mpl::size<lUnifiers>, boost::mpl::size<rUnifiers> >,
                boost::mpl::fold
                <
                    lUnifiers,
                    boost::mpl::true_,
                    boost::mpl::and_
                    <
                        boost::mpl::_1,
                        boost::is_same
                        <
                            lookup<rUnifiers, boost::mpl::first<boost::mpl::_2> >,
                            boost::mpl::second<boost::mpl::_2>
                        >
                    >
                >
            >
    {};
}

#endif
