/*
 * bitsetaux.cpp
 *
 *  Created on: 24/05/2014
 *      Author: ari
 */


// Choreado de acá http://stackoverflow.com/questions/16761472/how-can-i-increment-stdbitset

#include <bitset>

template <size_t N>
std::bitset<N> increment ( std::bitset<N> in ) {
//  add 1 to each value, and if it was 1 already, carry the 1 to the next.
    for ( size_t i = 0; i < N; ++i ) {
        if ( in[i] == 0 ) {  // There will be no carry
            in[i] = 1;
            break;
            }
        in[i] = 0;  // This entry was 1; set to zero and carry the 1
        }
    return in;
    }
