/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#define METALOG_MAX_VARIADIC_ARGS 4
#include "metalog/unify.hpp"
#include "metalog/detail/preprocessor.hpp"

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

#define METALOG_COMPARE_UNIFIERS(EXPECTED, DEDUCED) \
    boost::mpl::size<DEDUCED>::value == boost::mpl::size<EXPECTED>::value && \
    boost::mpl::fold \
    < \
        DEDUCED, \
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

#define METALOG_CHECK_UNIFICATION(ASSERTION) \
    ( \
        std::cout << std::endl << BOOST_PP_STRINGIZE((BOOST_PP_ARRAY_ENUM(BOOST_PP_SEQ_ELEM(1, ASSERTION)))), \
        ( \
            BOOST_PP_SEQ_ELEM(0, ASSERTION) == BOOST_PP_ARRAY_ENUM(BOOST_PP_SEQ_ELEM(1, ASSERTION))::value && \
            METALOG_COMPARE_UNIFIERS \
            ( \
                BOOST_PP_ARRAY_ENUM(BOOST_PP_SEQ_ELEM(2, ASSERTION)), \
                BOOST_PP_ARRAY_ENUM(BOOST_PP_SEQ_ELEM(1, ASSERTION))::unifiers \
            ) \
            ? (std::cout << " [SUCCEEDED]", true) \
            : (std::cout << " [FAILED]" << std::endl \
                         << "    expected result: " << (BOOST_PP_SEQ_ELEM(0, ASSERTION) ? "success" : "failure") << std::endl \
                         << "    expected unifiers: " << BOOST_PP_STRINGIZE((BOOST_PP_ARRAY_ENUM(BOOST_PP_SEQ_ELEM(2, ASSERTION)))) << std::endl, false) \
        ) \
    )

#define METALOG_FORWARD_CHECK(Z, N, ASSERTIONS) \
    BOOST_PP_COMMA_IF(N) METALOG_CHECK_UNIFICATION(BOOST_PP_SEQ_ELEM(N, ASSERTIONS))

#define METALOG_CHECK_ALL(ASSERTIONS) \
    BOOST_PP_REPEAT(BOOST_PP_SEQ_SIZE(ASSERTIONS), METALOG_FORWARD_CHECK, ASSERTIONS)

template<METALOG_VARIADIC_PARAMS(1, _)>
struct rel1;

template<typename, typename>
struct rel2;

template<METALOG_VARIADIC_PARAMS(3, _)>
struct rel3;

struct A;
struct B;
struct C;

#define TEST_SAMPLES \
    ((false)((2, (unify<int, void>                                                                          )))((1, (boost::mpl::map<>)))) \
    ((false)((4, (unify<rel2<int, int>, rel2<int, int*> >                                                   )))((1, (boost::mpl::map<>)))) \
    ((false)((3, (unify<rel1<int>, rel2<int, int*> >                                                        )))((1, (boost::mpl::map<>)))) \
    ((false)((4, (unify<rel2<int, void>, rel2<int, term<void> > >                                           )))((1, (boost::mpl::map<>)))) \
    ((false)((2, (unify<term<int>, rel1<int> >                                                              )))((1, (boost::mpl::map<>)))) \
    ((false)((4, (unify<term<int, int*>, rel2<int, int*> >                                                  )))((1, (boost::mpl::map<>)))) \
    ((false)((6, (unify<term<int, int*, int**>, rel3<int, int*, int**> >                                    )))((1, (boost::mpl::map<>)))) \
    ((false)((2, (unify<var<A>*, int *const >                                                               )))((1, (boost::mpl::map<>)))) \
    ((false)((2, (unify<var<A>[1], int[]>                                                                   )))((1, (boost::mpl::map<>)))) \
    ((false)((2, (unify<var<A>[2][1], int[][2][1]>                                                          )))((1, (boost::mpl::map<>)))) \
    ((false)((2, (unify<int *const, int[]>                                                                  )))((1, (boost::mpl::map<>)))) \
    ((false)((2, (unify<var<A>, rel1<var<A> > >                                                             )))((1, (boost::mpl::map<>)))) \
    ((false)((6, (unify<term<var<A>, term<term<int>, var<B> > >, term<term<var<B> >, term<var<A>, char> > > )))((1, (boost::mpl::map<>)))) \
    ((false)((6, (unify<rel3<var<A>, var<B>, var<C> >, rel3<var<B>, var<C>, rel1<var<A> > > >               )))((1, (boost::mpl::map<>)))) \
    ((false)((2, (unify<int, atom<int> >                                                                    )))((1, (boost::mpl::map<>)))) \
    ((false)((2, (unify<atom<int>, atom<int*> >                                                             )))((1, (boost::mpl::map<>)))) \
    ((false)((2, (unify<atom<var<A> >, atom<int> >                                                          )))((1, (boost::mpl::map<>)))) \
    ((false)((4, (unify<rel2<int, atom<var<A> > >, rel2<var<A>, atom<int> > >                               )))((1, (boost::mpl::map<>)))) \
    ((true )((2, (unify<void, void>                                                                         )))((1, (boost::mpl::map<>)))) \
    ((true )((2, (unify<var<A>, void>                                                                       )))((2, (boost::mpl::map<boost::mpl::pair<var<A>, void> >)))) \
    ((true )((2, (unify<var<A>*, void*>                                                                     )))((2, (boost::mpl::map<boost::mpl::pair<var<A>, void> >)))) \
    ((true )((2, (unify<var<A>*, var<B> >                                                                   )))((2, (boost::mpl::map<boost::mpl::pair<var<B>, var<A>*> >)))) \
    ((true )((2, (unify<var<A>&, int const&>                                                                )))((2, (boost::mpl::map<boost::mpl::pair<var<A>, int const> >)))) \
    ((true )((2, (unify<var<A>&, int(&)[]>                                                                  )))((2, (boost::mpl::map<boost::mpl::pair<var<A>, int[]> >)))) \
    ((true )((2, (unify<var<A> const, int const[10]>                                                        )))((2, (boost::mpl::map<boost::mpl::pair<var<A>, int[10]> >)))) \
    ((true )((2, (unify<var<A>(*)[5], int(*)[5][3]>                                                         )))((2, (boost::mpl::map<boost::mpl::pair<var<A>, int[3]> >)))) \
    ((true )((2, (unify<var<A> volatile, void volatile>                                                     )))((2, (boost::mpl::map<boost::mpl::pair<var<A>, void> >)))) \
    ((true )((2, (unify<var<A> volatile const* const volatile, volatile const float* const volatile>        )))((2, (boost::mpl::map<boost::mpl::pair<var<A>, float> >)))) \
    ((true )((2, (unify<const var<A> volatile, var<B> const>                                                )))((2, (boost::mpl::map<boost::mpl::pair<var<B>, var<A> volatile> >)))) \
    ((true )((2, (unify<var<A>, var<A> >                                                                    )))((1, (boost::mpl::map<>)))) \
    ((true )((2, (unify<var<A>, var<B> >                                                                    )))((2, (boost::mpl::map<boost::mpl::pair<var<A>, var<B> > >)))) \
    ((true )((3, (unify<var<A>, term<int, int*> >                                                           )))((3, (boost::mpl::map<boost::mpl::pair<var<A>, term<int, int*> > >)))) \
    ((true )((2, (unify<term<int>, term<int> >                                                              )))((1, (boost::mpl::map<>)))) \
    ((true )((4, (unify<term<int, int*>, term<int, int*> >                                                  )))((1, (boost::mpl::map<>)))) \
    ((true )((4, (unify<term<term<int, int*> >, term<term<int, int*> > >                                    )))((1, (boost::mpl::map<>)))) \
    ((true )((8, (unify<term<int*, int[], int[1], int&>, term<int*, int[], int[1], int&> >                  )))((1, (boost::mpl::map<>)))) \
    ((true )((4, (unify<term<var<A>, var<B> >, term<int, int*> >                                            )))((4, (boost::mpl::map<boost::mpl::pair<var<A>, int>, boost::mpl::pair<var<B>, int*> >)))) \
    ((true )((4, (unify<term<int, var<A> >, term<int, int*> >                                               )))((2, (boost::mpl::map<boost::mpl::pair<var<A>, int*> >)))) \
    ((true )((4, (unify<term<var<A>, var<A>*>, term<int, int*> >                                            )))((2, (boost::mpl::map<boost::mpl::pair<var<A>, int> >)))) \
    ((true )((4, (unify<term<var<A>, var<B> >, term<var<B>, int> >                                          )))((4, (boost::mpl::map<boost::mpl::pair<var<A>, int>, boost::mpl::pair<var<B>, int> >)))) \
    ((true )((6, (unify<term<var<A>, term<term<int>, var<B> > >, term<term<var<B> >, term<var<A>, int> > >  )))((4, (boost::mpl::map<boost::mpl::pair<var<A>, term<int> >, boost::mpl::pair<var<B>, int> >)))) \
    ((true )((2, (unify<rel1<int>, rel1<int> >                                                              )))((1, (boost::mpl::map<>)))) \
    ((true )((4, (unify<rel2<int, int*>, rel2<int, int*> >                                                  )))((1, (boost::mpl::map<>)))) \
    ((true )((4, (unify<rel1<term<int, var<A>*> >, rel1<term<int, int**> > >                                )))((2, (boost::mpl::map<boost::mpl::pair<var<A>, int*> >)))) \
    ((true )((2, (unify<rel1<var<A> >, rel1<int> >                                                          )))((2, (boost::mpl::map<boost::mpl::pair<var<A>, int> >)))) \
    ((true )((4, (unify<rel2<var<A>, var<B> >, rel2<int, int*> >                                            )))((4, (boost::mpl::map<boost::mpl::pair<var<A>, int>, boost::mpl::pair<var<B>, int*> >)))) \
    ((true )((4, (unify<rel2<int, var<A> >, rel2<int, int*> >                                               )))((2, (boost::mpl::map<boost::mpl::pair<var<A>, int*> >)))) \
    ((true )((4, (unify<rel2<var<A>, var<A>*>, rel2<int, int*> >                                            )))((2, (boost::mpl::map<boost::mpl::pair<var<A>, int> >)))) \
    ((true )((4, (unify<rel2<var<A>, var<B> >, rel2<var<B>, int> >                                          )))((4, (boost::mpl::map<boost::mpl::pair<var<A>, int>, boost::mpl::pair<var<B>, int> >)))) \
    ((true )((6, (unify<rel3<int, var<A>, var<B> >, rel3<int, var<B>, int> >                                )))((4, (boost::mpl::map<boost::mpl::pair<var<A>, int>, boost::mpl::pair<var<B>, int> >)))) \
    ((true )((6, (unify<rel3<var<A>, var<B>, var<C> >, rel3<var<B>, var<C>, int> >                          )))((6, (boost::mpl::map<boost::mpl::pair<var<A>, int>, boost::mpl::pair<var<B>, int>, boost::mpl::pair<var<C>, int> >)))) \
    ((true )((6, (unify<rel3<var<A>, var<A>, var<C> >, rel3<int, var<C>, var<B> > >                         )))((6, (boost::mpl::map<boost::mpl::pair<var<A>, int>, boost::mpl::pair<var<B>, int>, boost::mpl::pair<var<C>, int> >)))) \
    ((true )((6, (unify<rel3<var<A>, var<C>, var<B> >, rel3<var<B>, int, var<C> > >                         )))((6, (boost::mpl::map<boost::mpl::pair<var<A>, int>, boost::mpl::pair<var<B>, int>, boost::mpl::pair<var<C>, int> >)))) \
    ((true )((6, (unify<rel2<var<A>, rel2<rel1<int>, var<B> > >, rel2<rel1<var<B> >, rel2<var<A>, int> > >  )))((4, (boost::mpl::map<boost::mpl::pair<var<A>, rel1<int> >, boost::mpl::pair<var<B>, int> >)))) \
    ((true )((2, (unify<atom<int>, atom<int> >                                                              )))((1, (boost::mpl::map<>)))) \
    ((true )((2, (unify<var<A>, atom<var<A> > >                                                             )))((2, (boost::mpl::map<boost::mpl::pair<var<A>, atom<var<A> > > >)))) \


int main()
{
    using namespace metalog;
    bool const results[] = {METALOG_CHECK_ALL(TEST_SAMPLES)};

    std::cout << std::endl;

    std::size_t const ok = std::count_if(results, results + sizeof(results), boost::bind(std::equal_to<bool>(), true, _1));

    std::cout << std::endl;
    std::cout << std::setw(3) << ok << '/' << sizeof(results) << " SUCCEEDED" << std::endl;
    std::cout << std::setw(3) << sizeof(results) - ok << '/' << sizeof(results) << " FAILED" << std::endl;
    std::cout << std::endl;

    return !std::accumulate(results, results + sizeof(results), true, std::logical_and<bool>());
}
