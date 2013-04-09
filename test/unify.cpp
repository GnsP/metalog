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
                         << "    expected unifiers: " << BOOST_PP_STRINGIZE(BOOST_PP_SEQ_ELEM(2, ASSERTION)) << std::endl, false) \
        ) \
    )

#define MUNIFY_FORWARD_CHECK(Z, N, ASSERTIONS) \
    BOOST_PP_COMMA_IF(N) MUNIFY_CHECK_UNIFICATION(BOOST_PP_SEQ_ELEM(N, ASSERTIONS))

#define MUNIFY_CHECK_ALL(ASSERTIONS) \
    BOOST_PP_REPEAT(BOOST_PP_SEQ_SIZE(ASSERTIONS), MUNIFY_FORWARD_CHECK, ASSERTIONS)

template<typename...>
struct rel;

template<typename... T>
struct unifiers : boost::mpl::map<T...>
{};

template<typename key, typename value>
struct entry : boost::mpl::pair<key, value>
{};

#define NOT_UNIFIABLE \
    ((false)((02, (unify<int, void>                                                                         )))((01, (unifiers<>)))) \
    ((false)((04, (unify<rel<int, int>, rel<int, int*> >                                                    )))((01, (unifiers<>)))) \
    ((false)((03, (unify<rel<int>, rel<int, int*> >                                                         )))((01, (unifiers<>)))) \
    ((false)((04, (unify<rel<int, void>, rel<int, term<void> > >                                            )))((01, (unifiers<>)))) \
    ((false)((02, (unify<term<int>, rel<int> >                                                              )))((01, (unifiers<>)))) \
    ((false)((04, (unify<term<int, int*>, rel<int, int*> >                                                  )))((01, (unifiers<>)))) \
    ((false)((06, (unify<term<int, int*, int**>, rel<int, int*, int**> >                                    )))((01, (unifiers<>)))) \
    ((false)((02, (unify<var<1>*, int *const >                                                              )))((01, (unifiers<>)))) \
    ((false)((02, (unify<var<1>, rel<var<1> > >                                                             )))((01, (unifiers<>)))) \
    ((false)((02, (unify<int, atom<int> >                                                                   )))((01, (unifiers<>)))) \
    ((false)((02, (unify<atom<int>, atom<int*> >                                                            )))((01, (unifiers<>)))) \
    ((false)((02, (unify<atom<var<1> >, atom<int> >                                                         )))((01, (unifiers<>)))) \
    ((false)((04, (unify<rel<int, atom<var<1> > >, rel<var<1>, atom<int> > >                                )))((01, (unifiers<>)))) \

#define UNIFIABLE \
    ((true )((02, (unify<void, void>                                                                        )))((01, (unifiers<>)))) \
    ((true )((02, (unify<var<1>, void>                                                                      )))((02, (unifiers<entry<var<1>, void> >)))) \
    ((true )((02, (unify<var<1>*, void*>                                                                    )))((02, (unifiers<entry<var<1>, void> >)))) \
    ((true )((02, (unify<var<1>*, var<2>*>                                                                  )))((02, (unifiers<entry<var<1>, var<2> > >)))) \
    ((true )((02, (unify<const var<1> volatile, var<1> const volatile>                                      )))((01, (unifiers<>)))) \
    ((true )((02, (unify<var<1>&, int const&>                                                               )))((02, (unifiers<entry<var<1>, int const> >)))) \
    ((true )((02, (unify<var<1>&&, int&&>                                                                   )))((02, (unifiers<entry<var<1>, int> >)))) \
    ((true )((02, (unify<var<1> volatile, void volatile>                                                    )))((02, (unifiers<entry<var<1>, void> >)))) \
    ((true )((02, (unify<var<1> volatile const* const volatile, volatile const float* const volatile>       )))((02, (unifiers<entry<var<1>, float> >)))) \
    ((true )((02, (unify<var<1>, var<1> >                                                                   )))((01, (unifiers<>)))) \
    ((true )((02, (unify<var<1>, var<2> >                                                                   )))((02, (unifiers<entry<var<1>, var<2> > >)))) \
    ((true )((03, (unify<var<1>, term<int, int*> >                                                          )))((03, (unifiers<entry<var<1>, term<int, int*> > >)))) \
    ((true )((02, (unify<term<int>, term<int> >                                                             )))((01, (unifiers<>)))) \
    ((true )((04, (unify<term<int, int*>, term<int, int*> >                                                 )))((01, (unifiers<>)))) \
    ((true )((04, (unify<term<term<int, int*> >, term<term<int, int*> > >                                   )))((01, (unifiers<>)))) \
    ((true )((10, (unify<term<int, int*, float, float*, void>, term<int, int*, float, float*, void> >       )))((01, (unifiers<>)))) \
    ((true )((04, (unify<term<var<1>, var<2> >, term<int, int*> >                                           )))((04, (unifiers<entry<var<1>, int>, entry<var<2>, int*> >)))) \
    ((true )((04, (unify<term<int, var<1> >, term<int, int*> >                                              )))((02, (unifiers<entry<var<1>, int*> >)))) \
    ((true )((04, (unify<term<var<1>, var<1>*>, term<int, int*> >                                           )))((02, (unifiers<entry<var<1>, int> >)))) \
    ((true )((04, (unify<term<var<1>, var<2> >, term<var<2>, int> >                                         )))((04, (unifiers<entry<var<1>, int>, entry<var<2>, int> >)))) \
    ((true )((06, (unify<term<var<1>, term<term<int>, var<2> > >, term<term<var<2> >, term<var<1>, int> > > )))((04, (unifiers<entry<var<1>, term<int> >, entry<var<2>, int> >)))) \
    ((true )((02, (unify<rel<int>, rel<int> >                                                               )))((01, (unifiers<>)))) \
    ((true )((04, (unify<rel<int, int*>, rel<int, int*> >                                                   )))((01, (unifiers<>)))) \
    ((true )((04, (unify<rel<term<int, var<1>*> >, rel<term<int, int**> > >                                 )))((02, (unifiers<entry<var<1>, int*> >)))) \
    ((true )((10, (unify<rel<int, int*, float, float*, void>, rel<int, int*, float, float*, void> >         )))((01, (unifiers<>)))) \
    ((true )((02, (unify<rel<var<1> >, rel<int> >                                                           )))((02, (unifiers<entry<var<1>, int> >)))) \
    ((true )((04, (unify<rel<var<1>, var<2> >, rel<int, int*> >                                             )))((04, (unifiers<entry<var<1>, int>, entry<var<2>, int*> >)))) \
    ((true )((04, (unify<rel<int, var<1> >, rel<int, int*> >                                                )))((02, (unifiers<entry<var<1>, int*> >)))) \
    ((true )((04, (unify<rel<var<1>, var<1>*>, rel<int, int*> >                                             )))((02, (unifiers<entry<var<1>, int> >)))) \
    ((true )((04, (unify<rel<var<1>, var<2> >, rel<var<2>, int> >                                           )))((04, (unifiers<entry<var<1>, int>, entry<var<2>, int> >)))) \
    ((true )((06, (unify<rel<int, var<1>, var<2> >, rel<int, var<2>, int> >                                 )))((04, (unifiers<entry<var<1>, int>, entry<var<2>, int> >)))) \
    ((true )((06, (unify<rel<var<1>, var<2>, var<3> >, rel<var<2>, var<3>, int> >                           )))((06, (unifiers<entry<var<1>, int>, entry<var<2>, int>, entry<var<3>, int> >)))) \
    ((true )((06, (unify<rel<var<1>, var<1>, var<3> >, rel<int, var<3>, var<2> > >                          )))((06, (unifiers<entry<var<1>, int>, entry<var<2>, int>, entry<var<3>, int> >)))) \
    ((true )((06, (unify<rel<var<1>, var<3>, var<2> >, rel<var<2>, int, var<3> > >                          )))((06, (unifiers<entry<var<1>, int>, entry<var<2>, int>, entry<var<3>, int> >)))) \
    ((true )((06, (unify<rel<var<1>, rel<rel<int>, var<2> > >, rel<rel<var<2> >, rel<var<1>, int> > >       )))((04, (unifiers<entry<var<1>, rel<int> >, entry<var<2>, int> >)))) \
    ((true )((02, (unify<atom<int>, atom<int> >                                                             )))((01, (unifiers<>)))) \
    ((true )((02, (unify<var<1>, atom<var<1> > >                                                            )))((02, (unifiers<entry<var<1>, atom<var<1> > > >)))) \

int main()
{
    using namespace munify;
    bool const results[] = {MUNIFY_CHECK_ALL(NOT_UNIFIABLE UNIFIABLE)};

    std::cout << std::endl;

    std::size_t const ok = std::count_if(results, results + sizeof(results), boost::bind(std::equal_to<bool>(), true, _1));

    std::cout << std::endl;
    std::cout << std::setw(3) << ok << '/' << sizeof(results) << " SUCCEEDED" << std::endl;
    std::cout << std::setw(3) << sizeof(results) - ok << '/' << sizeof(results) << " FAILED" << std::endl;
    std::cout << std::endl;

    return !std::accumulate(results, results + sizeof(results), true, std::logical_and<bool>());
}
