/*
 * This file is part of munify, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#include "munify/unify.hpp"

#include <iostream>

#define TEST(expr) \
    { \
        bool const result = expr; \
        if(!result) \
        { \
            std::cout << #expr << std::endl; \
            return 1; \
        } \
    }

template<typename...>
struct rel;

template<typename>
struct rel1;

template<typename, typename>
struct rel2;

template<typename, typename, typename>
struct rel3;


int main()
{
    std::cout << std::endl;

    //not unifiable
    TEST((!munify::unify<int, void>::value))
    TEST((!munify::unify<rel2<int, int>, rel2<int, int*> >::value))
    TEST((!munify::unify<rel<int>, rel<int, int*> >::value))
//    TEST((!munify::unify<munify::var<1>, rel1<munify::var<1> > >::value))

    //unifiable
    TEST((munify::unify<void, void>::value))
    TEST((munify::unify<munify::var<1>, void>::value))
    TEST((munify::unify<munify::var<1>*, void*>::value))
    TEST((munify::unify<munify::var<1>*, munify::var<2>*>::value))
    TEST((munify::unify<const munify::var<1> volatile, munify::var<1> const volatile>::value))
    TEST((munify::unify<munify::var<1> const&, int const&>::value))
    TEST((munify::unify<munify::var<1>&&, int&&>::value))
    TEST((munify::unify<munify::var<1> volatile, void volatile>::value))
    TEST((munify::unify<munify::var<1> volatile const* const volatile, volatile const float* const volatile>::value))
    TEST((munify::unify<munify::var<1>, munify::var<1> >::value))
    TEST((munify::unify<munify::var<1>, munify::var<2> >::value))
    TEST((munify::unify<munify::var<1>, rel2<int, int*> >::value))
    TEST((munify::unify<rel1<int>, rel1<int> >::value))
    TEST((munify::unify<rel2<int, int*>, rel2<int, int*> >::value))
    TEST((munify::unify<rel1<rel2<int, int*> >, rel1<rel2<int, int*> > >::value))
    TEST((munify::unify<rel<int, int*, float, float*, void, void*>, rel<int, int*, float, float*, void, void*> >::value))
    TEST((munify::unify<rel2<munify::var<1>, munify::var<2> >, rel2<int, int*> >::value))
    TEST((munify::unify<rel2<int, munify::var<1> >, rel2<int, int*> >::value))
    TEST((munify::unify<rel2<munify::var<1>, int*>, rel2<int, int*> >::value))
    TEST((munify::unify<rel2<munify::var<1>, munify::var<2> >, rel2<munify::var<2>, int> >::value))
    TEST((munify::unify<rel2<munify::var<1>, rel2<rel1<int>, munify::var<2> > >, rel2<rel1<munify::var<2> >, rel2<munify::var<1>, int> > >::value))
    TEST((munify::unify<rel2<munify::var<100>, munify::var<100>*>, rel2<int, int*> >::value))

    return 0;
}
