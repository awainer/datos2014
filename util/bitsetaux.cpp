/*
 * bitsetaux.cpp
 *
 *  Created on: 24/05/2014
 *      Author: ari
 */

#ifndef BITAUX_H_
#define BITAUX_H_


#include <bitset>
#include <string>
#include <vector>

namespace std{

template <size_t N>
bitset<N> increment ( bitset<N> in ) {
    for ( size_t i = 0; i < in.size(); ++i ) {
        if ( in[i] == 0 ) {
            in[i] = 1;
            break;
            }
        in[i] = 0;
        }
    return in;
}
}
#endif
