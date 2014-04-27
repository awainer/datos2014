/*
 * DataBlock.cpp
 *
 *  Created on: 20/04/2014
 *      Author: ari
 */

#include "DataBlock.h"
#include <cstdlib>
#include <iostream>
#include <cstring>

namespace std {
DataBlock::DataBlock(){
	this->remaining_bits_count=0;
	// Si alguien encuentra una forma mas bonita de
	// inicializar esto, mas que bienvenida.
	unsigned char masks[] = {1,3,7,15,31,63,127,255};
	for (int i=0;i<8;i++)
		this->masks[i] = masks[i];
	// Evitemos los segfaults por vector vacío, dale?
	this->data.push_back(0);
}

void DataBlock::addByte(unsigned char data) {
	unsigned char new_byte,aux,bits_to_add;

	if(!this->remaining_bits_count){
		this->data[this->data.size()-1] = data;
		this->data.push_back(0);
	}
	else{
		//optimizable, seguro.
		bits_to_add =8 - this->remaining_bits_count;
		aux = data >> (bits_to_add);
		new_byte = this->data[this->data.size()-1] | aux;
		this->data.push_back(new_byte);
		this->data[this->data.size()-1] = data << bits_to_add;
		this->remaining_bits_count = 8 - remaining_bits_count;
	}

}

void DataBlock::addBits(unsigned char data, unsigned char count) {
	if (count>7)
		throw "No se pueden agregar mas de 7 bits con este metodo, usa addByte.";
		// No llega a formar byte
	//Enmascaro los bits que contienen información
	data = data & this->masks[count-1];
	if (this->remaining_bits_count + count < 8){
		this->data[this->data.size()-1] =  (this->data[this->data.size()-1] << count) | data;
		this->remaining_bits_count+=count;
	}else{
		unsigned char new_byte=0;
		//unsigned char bits_to_shift= this->remaining_bits_count + count - 8;
		unsigned char bits_to_shift= 8 - this->remaining_bits_count;
		//cerr << "shifting: " << (int)bits_to_shift <<endl;

		this->data[this->data.size()-1] =  (this->data[this->data.size()-1] <<  bits_to_shift) | (data >> (count -  bits_to_shift));

		new_byte = data | this->masks[bits_to_shift];
		this->data.push_back(new_byte);
		this->remaining_bits_count = (this->remaining_bits_count + count - 8);

	}

}



unsigned long int DataBlock::getSizeInBytes() {
	if(!this->remaining_bits_count)
		return this->data.size() - 1;
	return this->data.size();
}


unsigned long int DataBlock::getSizeInBits() {
		return (8*(this->data.size() -1) + this->remaining_bits_count);
}

vector<unsigned char>::iterator DataBlock::getIterator(){
	return this->data.begin();
}

DataBlock::~DataBlock() {
	delete &(this->data);
}

} /* namespace std */


