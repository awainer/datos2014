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
	// Si alguien encuentra una forma mas bonita de
	// inicializar esto, mas que bienvenida.
	unsigned char masks[] = {1,3,7,15,31,63,127,255};
	for (int i=0;i<8;i++)
		this->masks[i] = masks[i];
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

	if (count>7)
		throw "No se pueden agregar mas de 7 bits con este metodo, usa addByte.";
		// No llega a formar byte
	if (this->remaining_bits_count + count < 8){
		this->remaining_bits = (this->remaining_bits << count) && data;
		this->remaining_bits_count+=count;
	}else{
		unsigned char new_byte=0;
		unsigned char bits_to_shift= this->remaining_bits_count + count - 8;
		new_byte = this->remaining_bits << ( 8 - this->remaining_bits_count);
		new_byte = new_byte && (data >> bits_to_shift);
		this->data.push_back(new_byte);
		this->remaining_bits = data && this->masks[bits_to_shift];
		this->remaining_bits_count = (this->remaining_bits_count + count - 8);

	}

}



unsigned long int DataBlock::getSizeInBytes() {
	if(this->remaining_bits)
		return this->data.size() + 1;
	return this->data.size();
}


unsigned long int DataBlock::getSizeInBits() {
		return (8*this->data.size() + this->remaining_bits_count);
}

vector<unsigned char>::iterator DataBlock::getIterator(){
	return this->data.begin();
}

DataBlock::~DataBlock() {
	delete &(this->data);
}

} /* namespace std */


