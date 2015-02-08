/*
 * This file is part of metalog, a free software.
 * Use, modification and distribution is subject to the BSD 2-clause license.
 * See accompanying file LICENSE.txt for its full text.
 */

#define METALOG_MAX_ARGS 23

#include "metalog.hpp"

#include <boost/mpl/vector.hpp>

using namespace metalog;

namespace genealogy
{
    template<typename, typename>
    struct grandparent;

    template<typename, typename>
    struct parent;

    template<typename, typename>
    struct father;

    template<typename, typename>
    struct mother;

    template<typename, typename>
    struct sibling;

    template<typename, typename>
    struct spouse;

    template<typename, typename>
    struct uncle;

    template<typename, typename>
    struct aunt;

    struct marvin;
    struct randy;
    struct sharon;
    struct stan;
    struct shelly;
    struct jimbo;
    struct flo;

    struct A;
    struct B;
    struct C;
    struct D;
    struct E;
    struct F;
    struct G;
    struct H;
    struct I;
    struct J;

    typedef boost::mpl::vector
    <
        clause<father<marvin, randy> >,
        clause<father<randy, stan> >,
        clause<father<randy, shelly> >,
        clause<spouse<randy, sharon> >,
        clause<sibling<randy, jimbo> >,
        clause<aunt<flo, sharon> >,
        clause<sibling<var<A>, var<B> >, conjunction<parent<var<C>, var<A> >, parent<var<C>, var<B> > > >,
        clause<parent<var<D>, var<E> >, conjunction<father<var<D>, var<E> > > >,
        clause<parent<var<F>, var<G> >, conjunction<mother<var<F>, var<G> > > >,
        clause<grandparent<var<H>, var<I> >, conjunction<parent<var<J>, var<I> >, parent<var<H>, var<J> > > >
    > clauses;

}

struct X;

int main()
{
    typedef resolve<genealogy::father<var<X>, genealogy::stan>, genealogy::clauses> sample;

    return !boost::mpl::and_
            <
                boost::mpl::true_,
                sample,
                boost::mpl::bool_<boost::mpl::size<sample::solution>::value == 1>,
                boost::mpl::has_key<boost::mpl::front<sample::solution>::type, var<X> >,
                boost::is_same
                <
                    boost::mpl::at<boost::mpl::front<sample::solution>::type, var<X> >::type,
                    genealogy::randy
                >
            >::type::value;
}
