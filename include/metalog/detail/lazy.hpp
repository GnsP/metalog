/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _METALOG_DETAIL_LAZY_HPP_
#define _METALOG_DETAIL_LAZY_HPP_

#include <boost/mpl/apply_wrap.hpp>

namespace metalog
{
    namespace detail
    {
        template<typename f>
        struct lazy :
                boost::mpl::apply_wrap0<f>
        {};
    }
}

#endif
