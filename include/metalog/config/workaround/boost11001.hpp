/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _METALOG_CONFIG_WORKAROUND_BOOST11001_HPP_
#define _METALOG_CONFIG_WORKAROUND_BOOST11001_HPP_

#include <boost/mpl/insert_range_fwd.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/mpl/clear.hpp>
#include <boost/mpl/joint_view.hpp>
#include <boost/mpl/iterator_range.hpp>
#include <boost/mpl/map/aux_/tag.hpp>

namespace boost
{
    namespace mpl {

        template<>
        struct insert_range_impl< aux::map_tag >
        {
            template<typename Sequence, typename Pos, typename Range>
            struct apply :
                    fold
                    <
                        joint_view
                        <
                            iterator_range<typename begin<Sequence>::type,Pos>,
                            joint_view
                            <
                                Range,
                                iterator_range<Pos,typename end<Sequence>::type>
                            >
                        >,
                        typename clear<Sequence>::type,
                        insert<_1, end<_1>, _2>
                    >
            {};
        };
    }
}
#endif
