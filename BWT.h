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

public:
	BWT();
	BWT(DataBlock * original_block);
	DataBlock * transform(DataBlock * original_block);
//	std::string untransform(std::string cadena_ant);*/
	~BWT();
};

}

#endif // BWT_H
