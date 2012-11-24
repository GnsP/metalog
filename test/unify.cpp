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

int main()
{
    std::cout << std::endl;

    //not unifiable
    TEST((!munify::unify<int, void>::value))
    TEST((!munify::unify<munify::term<int, int>, munify::term<int, int*> >::value))
    TEST((!munify::unify<munify::term<int>, munify::term<int, int*> >::value))
    TEST((!munify::unify<munify::var<1>, munify::term<munify::var<1> > >::value))

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
    TEST((munify::unify<munify::var<1>, munify::term<int, int*> >::value))
    TEST((munify::unify<munify::term<int>, munify::term<int> >::value))
    TEST((munify::unify<munify::term<int, int*>, munify::term<int, int*> >::value))
    TEST((munify::unify<munify::term<munify::term<int, int*> >, munify::term<munify::term<int, int*> > >::value))
    TEST((munify::unify<munify::term<int, int*, float, float*, void, void*>, munify::term<int, int*, float, float*, void, void*> >::value))
    TEST((munify::unify<munify::term<munify::var<1>, munify::var<2> >, munify::term<int, int*> >::value))
    TEST((munify::unify<munify::term<int, munify::var<1> >, munify::term<int, int*> >::value))
    TEST((munify::unify<munify::term<munify::var<1>, int*>, munify::term<int, int*> >::value))
    TEST((munify::unify<munify::term<munify::var<1>, munify::var<2> >, munify::term<munify::var<2>, int> >::value))
    TEST((munify::unify<munify::term<munify::var<1>, munify::term<munify::term<int>, munify::var<2> > >, munify::term<munify::term<munify::var<2> >, munify::term<munify::var<1>, int> > >::value))
    TEST((munify::unify<munify::term<munify::var<100>, munify::var<100>*>, munify::term<int, int*> >::value))

    return 0;
}
