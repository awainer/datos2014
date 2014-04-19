/*
 * MTF.cpp
 *
 *  Created on: 18/04/2014
 *      Author: ari
 */

#include "MTF.h"
#include <algorithm>
#include <iostream>
#include <memory.h>

namespace std {


MTF::MTF() {
	unsigned short int initial_vector[] = { 32, 101, 111, 116, 110, 105, 97, 114, 115, 104, 108, 100,
				99, 117, 102, 109, 103, 112, 119, 121, 118, 98, 122, 107, 120, 106, 113, 96, 95, 94, 93, 92, 91,
				90, 9, 89, 88, 87, 86, 85, 84, 83, 82, 81, 80, 8, 79, 78, 77, 76, 75, 74, 73, 72, 71, 70, 7, 69,
				68, 67, 66, 65, 64,	63, 62, 61, 60, 6, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 5, 49,
				48, 47, 46, 45, 44, 43, 42, 41,	40, 4, 39, 38, 37, 36, 35, 34, 33, 31, 30, 3,
				29, 28, 27, 26, 255, 254, 253, 252, 251, 250, 25, 249,
				248, 247, 246, 245, 244, 243, 242, 241, 240, 24, 239, 238, 237, 236, 235, 234, 233, 232, 231,
				230, 23, 229, 228, 227, 226, 225, 224, 223, 222, 221, 220, 22, 219, 218, 217, 216, 215, 214,
				213, 212, 211, 210, 21, 209, 208, 207, 206, 205, 204, 203, 202, 201, 200, 20, 2, 199, 198, 197,
				196, 195, 194, 193, 192, 191, 190, 19, 189, 188, 187, 186, 185, 184, 183, 182, 181, 180, 18, 179,
				178, 177, 176, 175, 174, 173, 172, 171, 170, 17, 169, 168, 167, 166, 165, 164, 163, 162, 161, 160,
				16, 159, 158, 157, 156, 155, 154, 153, 152, 151, 150, 15, 149, 148, 147, 146, 145, 144, 143, 142,
				141, 140, 14, 139, 138, 137, 136, 135, 134, 133, 132, 131, 130, 13, 129, 128, 127, 126, 125, 124,
				123, 12, 11, 10, 1, 0};
	for(int i=0;i<256;i++){
		this->initial_vector[i] = initial_vector[i];
	}
}

void MTF::resetStatus(){
	// Esto se puede optimizar. SEGURO.
	this->symbol_status.clear();
	for (int i=0; i<256; i++)
		this->symbol_status.push_back(this->initial_vector[i]);
}

void MTF::updateStatus(unsigned char lastpos){
	list<unsigned short int>::iterator it = this->symbol_status.begin();
	unsigned short int elem;



	if (lastpos == 0)
		return;
	advance(it,lastpos);
	elem = *it;
	this->symbol_status.erase(it);

	if (lastpos == 1)
		this->symbol_status.push_front(elem);
	else{
		it = this->symbol_status.begin();
		advance(it,1);
		this->symbol_status.insert(it,elem);
	}
}
unsigned char MTF::get_current_position(unsigned char c){

	list<unsigned short int>::iterator it = this->symbol_status.begin();
	char pos = 0;
	while(it != this->symbol_status.end()){
		//cout << "comparo con" <<  (int)*it << endl;
		if (*it == c)
			return pos;
		pos++;
	it++;
	}
	return pos;
}


/**
 * Algoritmo B (Move-to-front)
 */
unsigned char * MTF::b(unsigned long int blockLenght,char * blockData){
	this->resetStatus();

	unsigned char * result =(unsigned char *) malloc(blockLenght);
	unsigned long int resultpos=0;

	for (unsigned long int i=0;i<blockLenght;i++){
		//cout << "Busco " << blockData[i] <<endl;
		result[resultpos] = this->get_current_position(blockData[i]);
		this->updateStatus(resultpos);
		//cout << "lo encontre en pos" <<result[resultpos] << endl;
		resultpos++;

	}
	return result;

}

MTF::~MTF() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
