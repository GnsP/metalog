/*
 * This file is part of munify, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#include "munify/unify.hpp"

#include <boost/bind.hpp>

#include <boost/mpl/size.hpp>
#include <boost/mpl/logical.hpp>

#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/array/size.hpp>
#include <boost/preprocessor/array/elem.hpp>
#include <boost/preprocessor/array/enum.hpp>
#include <boost/preprocessor/control/expr_if.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/comma_if.hpp>

#include <functional>
#include <algorithm>
#include <numeric>
#include <iostream>
#include <iomanip>

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
        std::cout << std::endl << BOOST_PP_STRINGIZE((BOOST_PP_ARRAY_ENUM(BOOST_PP_SEQ_ELEM(1, ASSERTION)))), \
        ( \
            BOOST_PP_SEQ_ELEM(0, ASSERTION) == BOOST_PP_ARRAY_ENUM(BOOST_PP_SEQ_ELEM(1, ASSERTION))::value && \
            MUNIFY_COMPARE_UNIFIERS \
            ( \
                BOOST_PP_ARRAY_ENUM(BOOST_PP_SEQ_ELEM(2, ASSERTION)), \
                typename BOOST_PP_ARRAY_ENUM(BOOST_PP_SEQ_ELEM(1, ASSERTION))::unifiers \
            ) \
            ? (std::cout << " [SUCCEEDED]", true) \
            : (std::cout << " [FAILED]" << std::endl \
                         << "    expected result: " << (BOOST_PP_SEQ_ELEM(0, ASSERTION) ? "success" : "failure") << std::endl \
                         << "    expected unifiers: " << BOOST_PP_STRINGIZE((BOOST_PP_ARRAY_ENUM(BOOST_PP_SEQ_ELEM(2, ASSERTION)))) << std::endl, false) \
        ) \
    )

#define MUNIFY_FORWARD_CHECK(Z, N, ASSERTIONS) \
    BOOST_PP_COMMA_IF(N) MUNIFY_CHECK_UNIFICATION(BOOST_PP_SEQ_ELEM(N, ASSERTIONS))

#define MUNIFY_CHECK_ALL(ASSERTIONS) \
    BOOST_PP_REPEAT(BOOST_PP_SEQ_SIZE(ASSERTIONS), MUNIFY_FORWARD_CHECK, ASSERTIONS)

template<typename>
struct rel1;

template<typename, typename>
struct rel2;

template<typename, typename, typename>
struct rel3;

#define TEST_SAMPLES \
    ((false)((2, (unify<int, void>                                                                          )))((1, (boost::mpl::map<>)))) \
    ((false)((4, (unify<rel2<int, int>, rel2<int, int*> >                                                   )))((1, (boost::mpl::map<>)))) \
    ((false)((3, (unify<rel1<int>, rel2<int, int*> >                                                        )))((1, (boost::mpl::map<>)))) \
    ((false)((4, (unify<rel2<int, void>, rel2<int, term<void> > >                                           )))((1, (boost::mpl::map<>)))) \
    ((false)((2, (unify<term<int>, rel1<int> >                                                              )))((1, (boost::mpl::map<>)))) \
    ((false)((4, (unify<term<int, int*>, rel2<int, int*> >                                                  )))((1, (boost::mpl::map<>)))) \
    ((false)((6, (unify<term<int, int*, int**>, rel3<int, int*, int**> >                                    )))((1, (boost::mpl::map<>)))) \
    ((false)((2, (unify<var<1>*, int *const >                                                               )))((1, (boost::mpl::map<>)))) \
    ((false)((2, (unify<var<1>, rel1<var<1> > >                                                             )))((1, (boost::mpl::map<>)))) \
    ((false)((6, (unify<term<var<1>, term<term<int>, var<2> > >, term<term<var<2> >, term<var<1>, char> > > )))((1, (boost::mpl::map<>)))) \
    ((false)((6, (unify<rel3<var<1>, var<2>, var<3> >, rel3<var<2>, var<3>, rel1<var<1> > > >               )))((1, (boost::mpl::map<>)))) \
    ((false)((2, (unify<int, atom<int> >                                                                    )))((1, (boost::mpl::map<>)))) \
    ((false)((2, (unify<atom<int>, atom<int*> >                                                             )))((1, (boost::mpl::map<>)))) \
    ((false)((2, (unify<atom<var<1> >, atom<int> >                                                          )))((1, (boost::mpl::map<>)))) \
    ((false)((4, (unify<rel2<int, atom<var<1> > >, rel2<var<1>, atom<int> > >                               )))((1, (boost::mpl::map<>)))) \
    ((true )((2, (unify<void, void>                                                                         )))((1, (boost::mpl::map<>)))) \
    ((true )((2, (unify<var<1>, void>                                                                       )))((2, (boost::mpl::map<boost::mpl::pair<var<1>, void> >)))) \
    ((true )((2, (unify<var<1>*, void*>                                                                     )))((2, (boost::mpl::map<boost::mpl::pair<var<1>, void> >)))) \
    ((true )((2, (unify<var<1>*, var<2>*>                                                                   )))((2, (boost::mpl::map<boost::mpl::pair<var<1>, var<2> > >)))) \
    ((true )((2, (unify<const var<1> volatile, var<1> const volatile>                                       )))((1, (boost::mpl::map<>)))) \
    ((true )((2, (unify<var<1>&, int const&>                                                                )))((2, (boost::mpl::map<boost::mpl::pair<var<1>, int const> >)))) \
    ((true )((2, (unify<var<1> volatile, void volatile>                                                     )))((2, (boost::mpl::map<boost::mpl::pair<var<1>, void> >)))) \
    ((true )((2, (unify<var<1> volatile const* const volatile, volatile const float* const volatile>        )))((2, (boost::mpl::map<boost::mpl::pair<var<1>, float> >)))) \
    ((true )((2, (unify<var<1>, var<1> >                                                                    )))((1, (boost::mpl::map<>)))) \
    ((true )((2, (unify<var<1>, var<2> >                                                                    )))((2, (boost::mpl::map<boost::mpl::pair<var<1>, var<2> > >)))) \
    ((true )((3, (unify<var<1>, term<int, int*> >                                                           )))((3, (boost::mpl::map<boost::mpl::pair<var<1>, term<int, int*> > >)))) \
    ((true )((2, (unify<term<int>, term<int> >                                                              )))((1, (boost::mpl::map<>)))) \
    ((true )((4, (unify<term<int, int*>, term<int, int*> >                                                  )))((1, (boost::mpl::map<>)))) \
    ((true )((4, (unify<term<term<int, int*> >, term<term<int, int*> > >                                    )))((1, (boost::mpl::map<>)))) \
    ((true )((8, (unify<term<int, int*, float, float*>, term<int, int*, float, float*> >                    )))((1, (boost::mpl::map<>)))) \
    ((true )((4, (unify<term<var<1>, var<2> >, term<int, int*> >                                            )))((4, (boost::mpl::map<boost::mpl::pair<var<1>, int>, boost::mpl::pair<var<2>, int*> >)))) \
    ((true )((4, (unify<term<int, var<1> >, term<int, int*> >                                               )))((2, (boost::mpl::map<boost::mpl::pair<var<1>, int*> >)))) \
    ((true )((4, (unify<term<var<1>, var<1>*>, term<int, int*> >                                            )))((2, (boost::mpl::map<boost::mpl::pair<var<1>, int> >)))) \
    ((true )((4, (unify<term<var<1>, var<2> >, term<var<2>, int> >                                          )))((4, (boost::mpl::map<boost::mpl::pair<var<1>, int>, boost::mpl::pair<var<2>, int> >)))) \
    ((true )((6, (unify<term<var<1>, term<term<int>, var<2> > >, term<term<var<2> >, term<var<1>, int> > >  )))((4, (boost::mpl::map<boost::mpl::pair<var<1>, term<int> >, boost::mpl::pair<var<2>, int> >)))) \
    ((true )((2, (unify<rel1<int>, rel1<int> >                                                              )))((1, (boost::mpl::map<>)))) \
    ((true )((4, (unify<rel2<int, int*>, rel2<int, int*> >                                                  )))((1, (boost::mpl::map<>)))) \
    ((true )((4, (unify<rel1<term<int, var<1>*> >, rel1<term<int, int**> > >                                )))((2, (boost::mpl::map<boost::mpl::pair<var<1>, int*> >)))) \
    ((true )((2, (unify<rel1<var<1> >, rel1<int> >                                                          )))((2, (boost::mpl::map<boost::mpl::pair<var<1>, int> >)))) \
    ((true )((4, (unify<rel2<var<1>, var<2> >, rel2<int, int*> >                                            )))((4, (boost::mpl::map<boost::mpl::pair<var<1>, int>, boost::mpl::pair<var<2>, int*> >)))) \
    ((true )((4, (unify<rel2<int, var<1> >, rel2<int, int*> >                                               )))((2, (boost::mpl::map<boost::mpl::pair<var<1>, int*> >)))) \
    ((true )((4, (unify<rel2<var<1>, var<1>*>, rel2<int, int*> >                                            )))((2, (boost::mpl::map<boost::mpl::pair<var<1>, int> >)))) \
    ((true )((4, (unify<rel2<var<1>, var<2> >, rel2<var<2>, int> >                                          )))((4, (boost::mpl::map<boost::mpl::pair<var<1>, int>, boost::mpl::pair<var<2>, int> >)))) \
    ((true )((6, (unify<rel3<int, var<1>, var<2> >, rel3<int, var<2>, int> >                                )))((4, (boost::mpl::map<boost::mpl::pair<var<1>, int>, boost::mpl::pair<var<2>, int> >)))) \
    ((true )((6, (unify<rel3<var<1>, var<2>, var<3> >, rel3<var<2>, var<3>, int> >                          )))((6, (boost::mpl::map<boost::mpl::pair<var<1>, int>, boost::mpl::pair<var<2>, int>, boost::mpl::pair<var<3>, int> >)))) \
    ((true )((6, (unify<rel3<var<1>, var<1>, var<3> >, rel3<int, var<3>, var<2> > >                         )))((6, (boost::mpl::map<boost::mpl::pair<var<1>, int>, boost::mpl::pair<var<2>, int>, boost::mpl::pair<var<3>, int> >)))) \
    ((true )((6, (unify<rel3<var<1>, var<3>, var<2> >, rel3<var<2>, int, var<3> > >                         )))((6, (boost::mpl::map<boost::mpl::pair<var<1>, int>, boost::mpl::pair<var<2>, int>, boost::mpl::pair<var<3>, int> >)))) \
    ((true )((6, (unify<rel2<var<1>, rel2<rel1<int>, var<2> > >, rel2<rel1<var<2> >, rel2<var<1>, int> > >  )))((4, (boost::mpl::map<boost::mpl::pair<var<1>, rel1<int> >, boost::mpl::pair<var<2>, int> >)))) \
    ((true )((2, (unify<atom<int>, atom<int> >                                                              )))((1, (boost::mpl::map<>)))) \
    ((true )((2, (unify<var<1>, atom<var<1> > >                                                             )))((2, (boost::mpl::map<boost::mpl::pair<var<1>, atom<var<1> > > >)))) \

int main()
{
    using namespace munify;
    bool const results[] = {MUNIFY_CHECK_ALL(TEST_SAMPLES)};

    std::cout << std::endl;

    std::size_t const ok = std::count_if(results, results + sizeof(results), boost::bind(std::equal_to<bool>(), true, _1));

    std::cout << std::endl;
    std::cout << std::setw(3) << ok << '/' << sizeof(results) << " SUCCEEDED" << std::endl;
    std::cout << std::setw(3) << sizeof(results) - ok << '/' << sizeof(results) << " FAILED" << std::endl;
    std::cout << std::endl;

    return !std::accumulate(results, results + sizeof(results), true, std::logical_and<bool>());
}
