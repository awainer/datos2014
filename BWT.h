/*
 * BWT.h
 *
 *  Created on: 27/04/2014
 *      Author: tavo
 */

#ifndef BWT_H
#define BWT_H
#include "CircularList.h"
#include "DataBlock.h"

namespace std{

class BWT {
private:
	char * vector_punteros [];
	CircularList * circular_list;
	bool nodeCompare(CircularListNode * n1, CircularListNode * n2);
	bool checkStringsEquals(CircularListNode * n1, CircularListNode * n2);
	bool charCompare(vector<unsigned char>::iterator it, unsigned long int pos_char1, unsigned long int pos_char2);

public:
	BWT();
	BWT(DataBlock * original_block);
	DataBlock * transform(DataBlock * original_block);
	DataBlock * untransform(DataBlock * cadena_ant);
	~BWT();
};

}

#endif // BWT_H
