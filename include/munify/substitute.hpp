/*
 * This file is part of munify, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#ifndef _MUNIFY_SUBSTITUTE_HPP_
#define _MUNIFY_SUBSTITUTE_HPP_

#include <boost/mpl/arg.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/map.hpp>
#include <boost/mpl/list.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/has_key.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>

namespace munify
{
    template<typename unifiers, typename expr>
    struct substitute
    {
            typedef expr type;
    };

    template<typename unifiers, int n>
    struct substitute<unifiers, boost::mpl::arg<n> >
    {
//            boost bug #3982
//            typedef typename boost::mpl::at<unifiers, boost::mpl::arg<n>, boost::mpl::arg<n> >::type type;

            typedef typename boost::mpl::eval_if
            <
                boost::mpl::has_key<unifiers, boost::mpl::arg<n> >,
                boost::mpl::at<unifiers, boost::mpl::arg<n> >,
                boost::mpl::identity<boost::mpl::arg<n> >
            >::type type;
    };

    template<typename unifiers, template<typename, typename...> class rel, typename... expr>
    class substitute<unifiers, rel<expr...> >
    {
        private:
            template<typename...>
            struct pack;

            template<typename, typename>
            struct cons;

            template<typename h, typename... t>
            struct cons<h, substitute::pack<t...> >
            {
                    typedef typename substitute::template pack<h, t...> type;
            };

            template<typename, template<typename...> class>
            struct unpack;

            template<typename... args, template<typename...> class receiver>
            struct unpack<substitute::pack<args...>, receiver>
            {
                    typedef receiver<args...> type;
            };

            template<typename from, template<typename...> class to>
            struct rewrap
            {
                    typedef typename substitute::template unpack
                    <
                        typename boost::mpl::reverse_fold
                        <
                            from,
                            typename substitute::template pack<>,
                            typename substitute::template cons<boost::mpl::_2, boost::mpl::_1>
                        >::type,
                        to
                    >::type type;
            };

        public:
            typedef typename substitute::template rewrap
            <
                typename boost::mpl::transform<boost::mpl::list<expr...>, substitute<unifiers, boost::mpl::_1> >::type,
                rel
            >::type type;
    };
}

#endif
