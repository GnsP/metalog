/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _METALOG_DETAIL_SEQUENCES_IMPL_HPP_
#define _METALOG_DETAIL_SEQUENCES_IMPL_HPP_

#include <boost/mpl/identity.hpp>

namespace metalog
{
    namespace detail
    {
        template<typename seq>
        struct seq_impl :
                boost::mpl::identity<typename seq::impl>
        {};
    }

}

#endif
