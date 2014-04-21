/*
 * DataBlock.cpp
 *
 *  Created on: 20/04/2014
 *      Author: ari
 */

#include "DataBlock.h"
#include <cstdlib>
#include <cstring>
#include <memory.h>
namespace std {

DataBlock::DataBlock(unsigned char * data, unsigned long int size_in_bytes, char remaining_bits, char remaining_bits_count) {
	this->data=data;
	this->size_in_bytes=size_in_bytes;
	this->remaining_bits=remaining_bits;
	this->next_byte = data + size_in_bytes;
	this->incomplete_byte.all= 0;
	if(remaining_bits)
		this->addBits(remaining_bits, remaining_bits_count);
}

void DataBlock::addBytes(unsigned char* data, unsigned long int count) {
	if(!this->remaining_bits){ // Estamos alineados a byte, iupi.
		// Pido mas memoria. Debería chequear que efectivamente
		// me la dan. Una optimización posible es alocar de mas, para no alocar cada vez,
		// aunque implica trackear cuantos bytes libres tengo.
		if(this->data) //Agrego
			this->data = (unsigned char*)realloc(this->data, this->size_in_bytes + count);
		else // Primera data
			this->data = (unsigned char*)malloc(count);

		this->next_byte = this->data + this->size_in_bytes; //porsi
		memcpy((void*)(this->next_byte),(const void *)data,count);
		this->next_byte+=count;
		this->size_in_bytes+=count;
	}
	else{
		//TODO!!!
	}

}

void DataBlock::addBits(unsigned char data, unsigned char count) {
}

unsigned long int DataBlock::getSizeInBytes() {
	if (this->remaining_bits > 0)
		return this->size_in_bytes + 1; //redondeo a byte con los bits sueltos
	else
		return this->size_in_bytes;
}

unsigned char * DataBlock::getalignedData(){
	return this->data; // Polémico, debería copiarlo?
}

unsigned long int DataBlock::getSizeInBits() {
	if(this->remaining_bits)
		return 8*this->size_in_bytes + this->remaining_bits;
	else
		return 8*this->size_in_bytes;
}

DataBlock::~DataBlock() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
