/*
 * This file is part of munify, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#include "munify/unify.hpp"

#include <boost/preprocessor/tuple/size.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/tuple/enum.hpp>
#include <boost/preprocessor/control/expr_if.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/stringize.hpp>

#include <iostream>

#define MUNIFY_CHECK(ASSERTION) \
    (!BOOST_PP_TUPLE_ENUM(ASSERTION)::value ? \
    std::cout << BOOST_PP_STRINGIZE(ASSERTION) << std::endl, false : true)

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
            (!unify<int, void>),
            (!unify<term<int, int>, term<int, int*> >),
            (!unify<term<int>, term<int, int*> >),
            (!unify<var<1>, term<var<1> > >),

            (unify<void, void>),
            (unify<var<1>, void>),
            (unify<var<1>*, void*>),
            (unify<var<1>*, var<2>*>),
            (unify<const var<1> volatile, var<1> const volatile>),
            (unify<var<1> const&, int const&>),
            (unify<var<1>&&, int&&>),
            (unify<var<1> volatile, void volatile>),
            (unify<var<1> volatile const* const volatile, volatile const float* const volatile>),
            (unify<var<1>, var<1> >),
            (unify<var<1>, var<2> >),
            (unify<var<1>, term<int, int*> >),
            (unify<term<int>, term<int> >),
            (unify<term<int, int*>, term<int, int*> >),
            (unify<term<term<int, int*> >, term<term<int, int*> > >),
            (unify<term<int, int*, float, float*, void, void*>, term<int, int*, float, float*, void, void*> >),
            (unify<term<var<1>, var<2> >, term<int, int*> >),
            (unify<term<int, var<1> >, term<int, int*> >),
            (unify<term<var<1>, int*>, term<int, int*> >),
            (unify<term<var<1>, var<2> >, term<var<2>, int> >),
            (unify<term<var<1>, term<term<int>, var<2> > >, term<term<var<2> >, term<var<1>, int> > >),
            (unify<term<var<100>, var<100>*>, term<int, int*> >)
        ))
    );
}
