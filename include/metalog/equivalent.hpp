/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _METALOG_EQUIVALENT_HPP_
#define _METALOG_EQUIVALENT_HPP_

#include "unifiers.hpp"

#include <boost/type_traits.hpp>

#include <boost/mpl/logical.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/has_key.hpp>
#include <boost/mpl/at.hpp>

namespace metalog
{
    template<typename uL, typename uR>
    struct equivalent :
            boost::mpl::and_
            <
                boost::mpl::equal_to<boost::mpl::size<unifiers<uL> >, boost::mpl::size<unifiers<uR> > >,
                boost::mpl::fold
                <
                    unifiers<uL>,
                    boost::mpl::true_,
                    boost::mpl::and_
                    <
                        boost::mpl::_1,
                        boost::mpl::and_
                        <
                            boost::mpl::has_key<unifiers<uR>, boost::mpl::first<boost::mpl::_2> >,
                            boost::is_same
                            <
                                boost::mpl::at<unifiers<uR>, boost::mpl::first<boost::mpl::_2> >,
                                boost::mpl::second<boost::mpl::_2>
                            >
                        >
                    >
                >
            >
    {};
}

#endif
