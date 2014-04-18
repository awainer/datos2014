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
		cout << "Busco " << blockData[i] <<endl;
		result[resultpos] = this->get_current_position(blockData[i]);
		cout << "lo encontre en pos" <<result[resultpos] << endl;
		resultpos++;

	}
	return result;

}

MTF::~MTF() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
