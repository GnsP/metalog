/*
 * This file is part of munify, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#include "munify/unify.hpp"

#include <boost/mpl/size.hpp>
#include <boost/mpl/logical.hpp>

#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/tuple/size.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/tuple/enum.hpp>
#include <boost/preprocessor/control/expr_if.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/comma_if.hpp>

#include <algorithm>
#include <iostream>

#define MUNIFY_COMPARE_UNIFIERS(EXPECTED, FOUND) \
    boost::mpl::size<FOUND>::value == boost::mpl::size<EXPECTED>::value && \
    boost::mpl::fold \
    < \
        FOUND, \
        boost::mpl::true_, \
        boost::mpl::and_ \
        < \
            boost::mpl::_1, \
            boost::mpl::and_ \
            < \
                boost::mpl::has_key<EXPECTED, boost::mpl::first<boost::mpl::_2> >, \
                boost::is_same \
                < \
                    boost::mpl::at<EXPECTED, boost::mpl::first<boost::mpl::_2> >, \
                    boost::mpl::second<boost::mpl::_2> \
                > \
            > \
        > \
    >::type::value

#define MUNIFY_CHECK_UNIFICATION(ASSERTION) \
    ( \
        std::cout << std::endl << BOOST_PP_STRINGIZE(BOOST_PP_TUPLE_ELEM(1, ASSERTION)), \
        BOOST_PP_TUPLE_ELEM(0, ASSERTION) != \
        BOOST_PP_TUPLE_ENUM(BOOST_PP_TUPLE_ELEM(1, ASSERTION))::value && \
        MUNIFY_COMPARE_UNIFIERS \
        ( \
            BOOST_PP_TUPLE_ENUM(BOOST_PP_TUPLE_ELEM(2, ASSERTION)), \
            typename BOOST_PP_TUPLE_ENUM(BOOST_PP_TUPLE_ELEM(1, ASSERTION))::unifiers \
        ) \
        ? (std::cout << " [NOT OK]" << std::endl \
                     << "    expected result: " << (BOOST_PP_TUPLE_ELEM(0, ASSERTION) ? "success" : "failure") << std::endl \
                     << "    expected unifiers: " << BOOST_PP_STRINGIZE(BOOST_PP_TUPLE_ELEM(2, ASSERTION)) << std::endl, false) \
        : (std::cout << " [OK]", true) \
    )

#define MUNIFY_FORWARD_CHECK(Z, N, ASSERTIONS) \
    BOOST_PP_COMMA_IF(N) MUNIFY_CHECK_UNIFICATION(BOOST_PP_SEQ_ELEM(N, ASSERTIONS))

#define MUNIFY_CHECK_ALL(ASSERTIONS) \
    BOOST_PP_REPEAT(BOOST_PP_SEQ_SIZE(ASSERTIONS), MUNIFY_FORWARD_CHECK, ASSERTIONS)

#define NOT_UNIFIABLE \
    ((false,    (unify<int, void>                                                                           ), (boost::mpl::map<>))) \
    ((false,    (unify<term<int, int>, term<int, int*> >                                                    ), (boost::mpl::map<>))) \
    ((false,    (unify<term<int>, term<int, int*> >                                                         ), (boost::mpl::map<>))) \
    ((false,    (unify<var<1>*, int *const >                                                                ), (boost::mpl::map<>))) \
    ((false,    (unify<var<1>, term<var<1> > >                                                              ), (boost::mpl::map<>))) \

#define UNIFIABLE \
    ((true,     (unify<void, void>                                                                          ), (boost::mpl::map<>))) \
    ((true,     (unify<var<1>, void>                                                                        ), (boost::mpl::map<boost::mpl::pair<var<1>, void> >))) \
    ((true,     (unify<var<1>*, void*>                                                                      ), (boost::mpl::map<boost::mpl::pair<var<1>, void> >))) \
    ((true,     (unify<var<1>*, var<2>*>                                                                    ), (boost::mpl::map<boost::mpl::pair<var<1>, var<2> > >))) \
    ((true,     (unify<const var<1> volatile, var<1> const volatile>                                        ), (boost::mpl::map<>))) \
    ((true,     (unify<var<1>&, int const&>                                                                 ), (boost::mpl::map<boost::mpl::pair<var<1>, int const> >))) \
    ((true,     (unify<var<1>&&, int&&>                                                                     ), (boost::mpl::map<boost::mpl::pair<var<1>, int> >))) \
    ((true,     (unify<var<1> volatile, void volatile>                                                      ), (boost::mpl::map<boost::mpl::pair<var<1>, void> >))) \
    ((true,     (unify<var<1> volatile const* const volatile, volatile const float* const volatile>         ), (boost::mpl::map<boost::mpl::pair<var<1>, float> >))) \
    ((true,     (unify<var<1>, var<1> >                                                                     ), (boost::mpl::map<>))) \
    ((true,     (unify<var<1>, var<2> >                                                                     ), (boost::mpl::map<boost::mpl::pair<var<1>, var<2> > >))) \
    ((true,     (unify<var<1>, term<int, int*> >                                                            ), (boost::mpl::map<boost::mpl::pair<var<1>, term<int, int*> > >))) \
    ((true,     (unify<term<int>, term<int> >                                                               ), (boost::mpl::map<>))) \
    ((true,     (unify<term<int, int*>, term<int, int*> >                                                   ), (boost::mpl::map<>))) \
    ((true,     (unify<term<term<int, int*> >, term<term<int, int*> > >                                     ), (boost::mpl::map<>))) \
    ((true,     (unify<term<int, int*, float, float*, void>, term<int, int*, float, float*, void> >         ), (boost::mpl::map<>))) \
    ((true,     (unify<term<var<1>, var<2> >, term<int, int*> >                                             ), (boost::mpl::map<boost::mpl::pair<var<1>, int>, boost::mpl::pair<var<2>, int*> >))) \
    ((true,     (unify<term<int, var<1> >, term<int, int*> >                                                ), (boost::mpl::map<boost::mpl::pair<var<1>, int*> >))) \
    ((true,     (unify<term<var<1>, var<1>*>, term<int, int*> >                                             ), (boost::mpl::map<boost::mpl::pair<var<1>, int> >))) \
    ((true,     (unify<term<var<1>, var<2> >, term<var<2>, int> >                                           ), (boost::mpl::map<boost::mpl::pair<var<1>, int>, boost::mpl::pair<var<2>, int> >))) \
    ((true,     (unify<term<var<1>, term<term<int>, var<2> > >, term<term<var<2> >, term<var<1>, int> > >   ), (boost::mpl::map<boost::mpl::pair<var<1>, term<int> >, boost::mpl::pair<var<2>, int> >))) \

int main()
{
    using namespace munify;
    bool const results[] = {MUNIFY_CHECK_ALL(NOT_UNIFIABLE UNIFIABLE)};
    std::cout << std::endl;
    return !std::accumulate(results, results + sizeof(results), true, [](bool a, bool b) -> bool {return a && b;});
}
