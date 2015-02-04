/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _METALOG_DETAIL_SEQUENCES_IMPL_HPP_
#define _METALOG_DETAIL_SEQUENCES_IMPL_HPP_

#include "../lazy.hpp"

#include <boost/mpl/identity.hpp>

namespace metalog
{
    namespace detail
    {
        namespace seq
        {
            template<typename seq>
            struct impl :
                   seq::impl
            {};

            template<typename impl>
            struct seq :
                    boost::mpl::identity<impl>
            {};

            template<typename expr>
            struct seq<lazy<expr> > :
                    lazy<expr>
            {};
        }
    }

}

#endif
