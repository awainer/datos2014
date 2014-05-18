/*
 * BWT.cpp
 *
 *  Created on: 27/04/2014
 *      Author: tavo
 */

#include "BWT.h"
#include "CircularList.h"
#include "DataBlock.h"
#include <string>
#include <vector>
#include <algorithm>    // std::sort

namespace std{

BWT::BWT() {
	this->circular_list = new CircularList();
}



DataBlock * BWT::transform(DataBlock * original_block) {
	DataBlock * result_block = new DataBlock;
	unsigned char un_char;
	vector<unsigned char>::iterator it = original_block->getIterator();

	for (unsigned long int i = 1; i <= original_block->getSizeInBytes(); i++){
		un_char = (*it);
		this->circular_list->addNode(un_char);
		it++;
	}

	//unsigned long int cant_chars = this->circular_list->getQuantityNodes();
	vector<list<CircularListNode *>::iterator> un_vector ();

	/*for (unsigned long int i = 1; i <= original_block->getSizeInBytes; i++){
		un_char = (*it);
		this->circular_list->addNode(un_char);
		it++;
	}*/

	//this->circular_list->getIteratorAt(i);


	//std::sort (myvector.begin()+4, myvector.end(), myfunction);
	//

	return result_block;

//	for(int i=0 ; i < cadena_orig.size;i++)
//		this->vector_punteros[i] = &cadena_orig[i];

}

BWT::~BWT() {
}

}
