/*
 * bitsetaux.cpp
 *
 *  Created on: 24/05/2014
 *      Author: ari
 */


// Choreado de acá http://stackoverflow.com/questions/16761472/how-can-i-increment-stdbitset

#ifndef BITAUX_H_
#define BITAUX_H_


#include <bitset>
#include <string>
#include <vector>

namespace std{

template <size_t N>
bitset<N> increment ( bitset<N> in ) {
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

/*string vector_bool_to_string(vector<bool> b){
	string  result;
	for (unsigned int i=0; i<b.size(); i++)
		if (b[i])
		     result.push_back('1');
		else
			result.push_back('0');
	return result;
}*/
}
#endif
