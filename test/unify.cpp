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

template<typename, typename...>
class rel;

template<typename... T>
struct unifiers : boost::mpl::map<T...>
{};

template<typename key, typename value>
struct entry : boost::mpl::pair<key, value>
{};

#define NOT_UNIFIABLE \
    ((false,    (unify<int, void>                                                                           ), (unifiers<>))) \
    ((false,    (unify<rel<int, int>, rel<int, int*> >                                                      ), (unifiers<>))) \
    ((false,    (unify<rel<int>, rel<int, int*> >                                                           ), (unifiers<>))) \
    ((false,    (unify<rel<int, void>, rel<int, term<void> > >                                              ), (unifiers<>))) \
    ((false,    (unify<term<int>, rel<int> >                                                                ), (unifiers<>))) \
    ((false,    (unify<term<int, int*>, rel<int, int*> >                                                    ), (unifiers<>))) \
    ((false,    (unify<term<int, int*, int**>, rel<int, int*, int**> >                                      ), (unifiers<>))) \
    ((false,    (unify<var<1>*, int *const >                                                                ), (unifiers<>))) \
    ((false,    (unify<var<1>, rel<var<1> > >                                                               ), (unifiers<>))) \

#define UNIFIABLE \
    ((true,     (unify<void, void>                                                                          ), (unifiers<>))) \
    ((true,     (unify<var<1>, void>                                                                        ), (unifiers<entry<var<1>, void> >))) \
    ((true,     (unify<var<1>*, void*>                                                                      ), (unifiers<entry<var<1>, void> >))) \
    ((true,     (unify<var<1>*, var<2>*>                                                                    ), (unifiers<entry<var<1>, var<2> > >))) \
    ((true,     (unify<const var<1> volatile, var<1> const volatile>                                        ), (unifiers<>))) \
    ((true,     (unify<var<1>&, int const&>                                                                 ), (unifiers<entry<var<1>, int const> >))) \
    ((true,     (unify<var<1>&&, int&&>                                                                     ), (unifiers<entry<var<1>, int> >))) \
    ((true,     (unify<var<1> volatile, void volatile>                                                      ), (unifiers<entry<var<1>, void> >))) \
    ((true,     (unify<var<1> volatile const* const volatile, volatile const float* const volatile>         ), (unifiers<entry<var<1>, float> >))) \
    ((true,     (unify<var<1>, var<1> >                                                                     ), (unifiers<>))) \
    ((true,     (unify<var<1>, var<2> >                                                                     ), (unifiers<entry<var<1>, var<2> > >))) \
    ((true,     (unify<var<1>, term<int, int*> >                                                            ), (unifiers<entry<var<1>, term<int, int*> > >))) \
    ((true,     (unify<term<int>, term<int> >                                                               ), (unifiers<>))) \
    ((true,     (unify<term<int, int*>, term<int, int*> >                                                   ), (unifiers<>))) \
    ((true,     (unify<term<term<int, int*> >, term<term<int, int*> > >                                     ), (unifiers<>))) \
    ((true,     (unify<term<int, int*, float, float*, void>, term<int, int*, float, float*, void> >         ), (unifiers<>))) \
    ((true,     (unify<term<var<1>, var<2> >, term<int, int*> >                                             ), (unifiers<entry<var<1>, int>, entry<var<2>, int*> >))) \
    ((true,     (unify<term<int, var<1> >, term<int, int*> >                                                ), (unifiers<entry<var<1>, int*> >))) \
    ((true,     (unify<term<var<1>, var<1>*>, term<int, int*> >                                             ), (unifiers<entry<var<1>, int> >))) \
    ((true,     (unify<term<var<1>, var<2> >, term<var<2>, int> >                                           ), (unifiers<entry<var<1>, int>, entry<var<2>, int> >))) \
    ((true,     (unify<term<var<1>, term<term<int>, var<2> > >, term<term<var<2> >, term<var<1>, int> > >   ), (unifiers<entry<var<1>, term<int> >, entry<var<2>, int> >))) \
    ((true,     (unify<rel<int>, rel<int> >                                                                 ), (unifiers<>))) \
    ((true,     (unify<rel<int, int*>, rel<int, int*> >                                                     ), (unifiers<>))) \
    ((true,     (unify<rel<term<int, var<1>*> >, rel<term<int, int**> > >                                   ), (unifiers<>))) \
    ((true,     (unify<rel<int, int*, float, float*, void>, rel<int, int*, float, float*, void> >           ), (unifiers<>))) \
    ((true,     (unify<rel<var<1> >, rel<int> >                                                             ), (unifiers<entry<var<1>, int> >))) \
    ((true,     (unify<rel<var<1>, var<2> >, rel<int, int*> >                                               ), (unifiers<entry<var<1>, int>, entry<var<2>, int*> >))) \
    ((true,     (unify<rel<int, var<1> >, rel<int, int*> >                                                  ), (unifiers<entry<var<1>, int*> >))) \
    ((true,     (unify<rel<var<1>, var<1>*>, rel<int, int*> >                                               ), (unifiers<entry<var<1>, int> >))) \
    ((true,     (unify<rel<var<1>, var<2> >, rel<var<2>, int> >                                             ), (unifiers<entry<var<1>, int>, entry<var<2>, int> >))) \
    ((true,     (unify<rel<var<1>, rel<rel<int>, var<2> > >, rel<rel<var<2> >, rel<var<1>, int> > >         ), (unifiers<entry<var<1>, rel<int> >, entry<var<2>, int> >))) \

int main()
{
    using namespace munify;
    bool const results[] = {MUNIFY_CHECK_ALL(NOT_UNIFIABLE UNIFIABLE)};

    std::cout << std::endl;

    std::size_t const ok = std::count_if(results, results + sizeof(results), [](bool v) -> bool {return v;});
    std::size_t const not_ok = std::count_if(results, results + sizeof(results), [](bool v) -> bool {return !v;});

    std::cout << std::endl;
    std::cout << std::setw(3) << ok << '/' << sizeof(results) << " SUCCEEDED" << std::endl;
    std::cout << std::setw(3) << not_ok << '/' << sizeof(results) << " FAILED" << std::endl;
    std::cout << std::endl;

    return !std::accumulate(results, results + sizeof(results), true, [](bool a, bool b) -> bool {return a && b;});
}
