/*
 * This file is part of munify, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _MUNIFY_UNWRAP_SEQUENCE_HPP_
#define _MUNIFY_UNWRAP_SEQUENCE_HPP_

#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/reverse_fold.hpp>

namespace munify
{
    template<typename from, template<typename...> class to>
    class unwrap_sequence
    {
        private:
            template<typename...>
            struct pack;

            template<typename, typename>
            struct pack_cons;

            template<typename h, typename... args>
            struct pack_cons<h, pack<args...> >
            {
                    typedef pack<h, args...> type;
            };

            template<typename, template<typename...> class>
            struct unwrap_pack;

            template<typename... args, template<typename...> class receiver>
            struct unwrap_pack<pack<args...>, receiver>
            {
                    typedef receiver<args...> type;
            };

        public:
            typedef typename unwrap_pack
            <
                typename boost::mpl::reverse_fold<from, pack<>, pack_cons<boost::mpl::_2, boost::mpl::_1> >::type,
                to
            >::type type;
    };
}

#endif
