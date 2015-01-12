/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _METALOG_MINIMIZE_HPP_
#define _METALOG_MINIMIZE_HPP_

#include "unifiers.hpp"
#include "substitute.hpp"

#include "detail/lazy.hpp"

#include <boost/mpl/identity.hpp>
#include <boost/mpl/bind.hpp>
#include <boost/mpl/quote.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/mpl/pair.hpp>

namespace metalog
{
    template<typename u>
    struct minimize :
            boost::mpl::identity
            <
                unifiers
                <
                    detail::lazy
                    <
                        boost::mpl::bind
                        <
                            boost::mpl::quote3<boost::mpl::fold>,
                            unifiers<u>,
                            unifiers<>,
                            boost::mpl::insert
                            <
                                boost::mpl::_1,
                                boost::mpl::pair
                                <
                                    boost::mpl::first<boost::mpl::_2>,
                                    boost::mpl::apply_wrap1<substitute<u>, boost::mpl::second<boost::mpl::_2> >
                                >
                            >
                        >
                    >
                >
            >
    {};
}

#endif
