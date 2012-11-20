/*
 * This file is part of munify, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#include "munify/unify.hpp"

#include <iostream>

template<typename, typename>
struct rel2;

template<typename, typename, typename>
struct rel3;


int main()
{
    std::cout << std::endl;
    std::cout << "not unifiable:" << std::endl;
    std::cout << "munify::unify<int, void>::value = " << munify::unify<int, void>::value << std::endl;
    std::cout << "munify::unify<rel2<int, int>, rel2<int, int*> >::value = " << munify::unify<rel2<int, int>, rel2<int, int*> >::value << std::endl;

    std::cout << std::endl;
    std::cout << "unifiable:" << std::endl;
    std::cout << "munify::unify<void, void>::value = " << munify::unify<void, void>::value << std::endl;
    std::cout << "munify::unify<munify::atom<void, int, double>, munify::atom<void, int, double> >::value = " << munify::unify<munify::atom<void, int, double>, munify::atom<void, int, double> >::value << std::endl;
    std::cout << "munify::unify<boost::mpl::_1, void>::value = " << munify::unify<boost::mpl::_1, void>::value << std::endl;
    std::cout << "munify::unify<boost::mpl::_1*, void*>::value = " << munify::unify<boost::mpl::_1*, void*>::value << std::endl;
    std::cout << "munify::unify<boost::mpl::_1, boost::mpl::_1>::value = " << munify::unify<boost::mpl::_1, boost::mpl::_1>::value << std::endl;
    std::cout << "munify::unify<boost::mpl::_1, boost::mpl::_2>::value = " << munify::unify<boost::mpl::_1, boost::mpl::_2>::value << std::endl;
    std::cout << "munify::unify<boost::mpl::_1, rel2<int, int*> >::value = " << munify::unify<boost::mpl::_1, rel2<int, int*> >::value << std::endl;
    std::cout << "munify::unify<rel2<int, int*>, rel2<int, int*> >::value = " << munify::unify<rel2<int, int*>, rel2<int, int*> >::value << std::endl;
    std::cout << "munify::unify<rel2<boost::mpl::_1, boost::mpl::_2>, rel2<int, int*> >::value = " << munify::unify<rel2<boost::mpl::_1, boost::mpl::_2>, rel2<int, int*> >::value << std::endl;
    std::cout << "munify::unify<rel2<int, boost::mpl::_1>, rel2<int, int*> >::value = " << munify::unify<rel2<int, boost::mpl::_1>, rel2<int, int*> >::value << std::endl;
    std::cout << "munify::unify<rel2<boost::mpl::_1, int*>, rel2<int, int*> >::value = " << munify::unify<rel2<boost::mpl::_1, int*>, rel2<int, int*> >::value << std::endl;
    std::cout << "munify::unify<rel2<boost::mpl::_1, boost::mpl::_1*>, rel2<int, int*> >::value = " << munify::unify<rel2<boost::mpl::_1, boost::mpl::_1*>, rel2<int, int*> >::value << std::endl;
    return 0;
}
