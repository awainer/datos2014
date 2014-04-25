/*
 * DataBlock.cpp
 *
 *  Created on: 20/04/2014
 *      Author: ari
 */

#include "DataBlock.h"
#include <cstdlib>
#include <cstring>

namespace std {
DataBlock::DataBlock(){
	this->remaining_bits=0;
	this->remaining_bits_count=0;
}

void DataBlock::addByte(unsigned char data) {
	unsigned char new_byte,aux,bits_to_add;
	if(!this->remaining_bits_count)
		this->data.push_back(data);
	else{
		//optimizable, seguro.
		bits_to_add =8 - this->remaining_bits_count;
		aux = data >> (bits_to_add);
		new_byte = this->remaining_bits && aux;
		this->data.push_back(new_byte);
		this->remaining_bits = data << bits_to_add;
		this->remaining_bits_count = 8 - remaining_bits_count;
	}

}

void DataBlock::addBits(unsigned char data, unsigned char count) {
	//unsigned char aux;
	if (count>7)
		throw "No se pueden agregar mas de 7 bits con este metodo, usa addByte.";
	if(!this->remaining_bits_count){
		this->remaining_bits=data;
		this->remaining_bits_count=count;
	}/*else{

			unsigned char bits_to_complete = 8 - this->remaining_bits_count;
			//TODO: hay que considerar los dos casos: en que se completa un byte
			// y cuando sobran bits
			//aux = (this->remaining_bits << bits_to_complete) && data ;

		}*/
	}



unsigned long int DataBlock::getSizeInBytes() {
	return (this->data.size() + (this->remaining_bits_count % 8)); //magic!
}


unsigned long int DataBlock::getSizeInBits() {
		return (8*this->data.size() + this->remaining_bits_count);
}

DataBlock::~DataBlock() {
	delete &(this->data);
}

} /* namespace std */


