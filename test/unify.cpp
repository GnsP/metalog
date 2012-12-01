/*
 * This file is part of munify, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#include "munify/unify.hpp"

#include <boost/mpl/size.hpp>
#include <boost/mpl/logical.hpp>

#include <boost/preprocessor/tuple/size.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/tuple/enum.hpp>
#include <boost/preprocessor/control/expr_if.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/stringize.hpp>

#include <iostream>


#define MUNIFY_CHECK(ASSERTION) \
    ( \
        !BOOST_PP_TUPLE_ENUM(BOOST_PP_TUPLE_ELEM(0, ASSERTION)) \
        ( \
            BOOST_PP_TUPLE_ENUM(BOOST_PP_TUPLE_ELEM(1, ASSERTION))::value && \
            boost::mpl::size<typename BOOST_PP_TUPLE_ENUM(BOOST_PP_TUPLE_ELEM(1, ASSERTION))::unifiers>::value == \
            boost::mpl::size<BOOST_PP_TUPLE_ENUM(BOOST_PP_TUPLE_ELEM(2, ASSERTION))>::value && \
            boost::mpl::fold \
            < \
                typename BOOST_PP_TUPLE_ENUM(BOOST_PP_TUPLE_ELEM(1, ASSERTION))::unifiers, \
                boost::mpl::true_, \
                boost::mpl::and_ \
                < \
                    boost::mpl::_1, \
                    boost::mpl::and_ \
                    < \
                        boost::mpl::has_key<BOOST_PP_TUPLE_ENUM(BOOST_PP_TUPLE_ELEM(2, ASSERTION)), boost::mpl::first<boost::mpl::_2> >, \
                        boost::is_same \
                        < \
                            boost::mpl::at<BOOST_PP_TUPLE_ENUM(BOOST_PP_TUPLE_ELEM(2, ASSERTION)), boost::mpl::first<boost::mpl::_2> >, \
                            boost::mpl::second<boost::mpl::_2> \
                        > \
                    > \
                > \
            >::type::value \
        ) ? std::cout << BOOST_PP_STRINGIZE(BOOST_PP_TUPLE_ELEM(1, ASSERTION)) << std::endl, false : true \
    )

#define MUNIFY_FORWARD_CHECK(Z, N, ASSERTIONS) \
    BOOST_PP_EXPR_IF(N, &&) MUNIFY_CHECK(BOOST_PP_TUPLE_ELEM(N, ASSERTIONS))

#define MUNIFY_CHECK_ALL(ASSERTIONS) \
    BOOST_PP_REPEAT(BOOST_PP_TUPLE_SIZE(ASSERTIONS), MUNIFY_FORWARD_CHECK, ASSERTIONS)

using namespace munify;

int main()
{
    std::cout << std::endl;

    return !
    (
        MUNIFY_CHECK_ALL
        ((
            ((!), (unify<int, void>), (boost::mpl::map<>)),
            ((!), (unify<term<int, int>, term<int, int*> >), (boost::mpl::map<>)),
            ((!), (unify<term<int>, term<int, int*> >), (boost::mpl::map<>)),
            ((!), (unify<var<1>*, int *const >), (boost::mpl::map<>)),
            ((!), (unify<var<1>, term<var<1> > >), (boost::mpl::map<>)),

            (( ), (unify<void, void>), (boost::mpl::map<>)),
            (( ), (unify<var<1>, void>), (boost::mpl::map<boost::mpl::pair<var<1>, void> >)),
            (( ), (unify<var<1>*, void*>), (boost::mpl::map<boost::mpl::pair<var<1>, void> >)),
            (( ), (unify<var<1>*, var<2>*>), (boost::mpl::map<boost::mpl::pair<var<1>, var<2> > >)),
            (( ), (unify<const var<1> volatile, var<1> const volatile>), (boost::mpl::map<>)),
            (( ), (unify<var<1>&, int const&>), (boost::mpl::map<boost::mpl::pair<var<1>, int const> >)),
            (( ), (unify<var<1>&&, int&&>), (boost::mpl::map<boost::mpl::pair<var<1>, int> >)),
            (( ), (unify<var<1> volatile, void volatile>), (boost::mpl::map<boost::mpl::pair<var<1>, void> >)),
            (( ), (unify<var<1> volatile const* const volatile, volatile const float* const volatile>), (boost::mpl::map<boost::mpl::pair<var<1>, float> >)),
            (( ), (unify<var<1>, var<1> >), (boost::mpl::map<>)),
            (( ), (unify<var<1>, var<2> >), (boost::mpl::map<boost::mpl::pair<var<1>, var<2> > >)),
            (( ), (unify<var<1>, term<int, int*> >), (boost::mpl::map<boost::mpl::pair<var<1>, term<int, int*> > >)),
            (( ), (unify<term<int>, term<int> >), (boost::mpl::map<>)),
            (( ), (unify<term<int, int*>, term<int, int*> >), (boost::mpl::map<>)),
            (( ), (unify<term<term<int, int*> >, term<term<int, int*> > >), (boost::mpl::map<>)),
            (( ), (unify<term<int, int*, float, float*, void, void*>, term<int, int*, float, float*, void, void*> >), (boost::mpl::map<>)),
            (( ), (unify<term<var<1>, var<2> >, term<int, int*> >), (boost::mpl::map<boost::mpl::pair<var<1>, int>, boost::mpl::pair<var<2>, int*> >)),
            (( ), (unify<term<int, var<1> >, term<int, int*> >), (boost::mpl::map<boost::mpl::pair<var<1>, int*> >)),
            (( ), (unify<term<var<1>, var<1>*>, term<int, int*> >), (boost::mpl::map<boost::mpl::pair<var<1>, int> >)),
            (( ), (unify<term<var<1>, var<2> >, term<var<2>, int> >), (boost::mpl::map<boost::mpl::pair<var<1>, int>, boost::mpl::pair<var<2>, int> >)),
            (( ), (unify<term<var<1>, term<term<int>, var<2> > >, term<term<var<2> >, term<var<1>, int> > >), (boost::mpl::map<boost::mpl::pair<var<1>, term<int> >, boost::mpl::pair<var<2>, int> >))
        ))
    );
}
