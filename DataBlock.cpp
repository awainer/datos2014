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

	// Si alguien encuentra una forma mas bonita de
	// inicializar esto, mas que bienvenida.
	this->initialize();
	// Evitemos los segfaults por vector vacío, dale?
	this->data = new vector<unsigned char>;
	this->data->push_back(0);
	this->remaining_bits_count=0;
}

DataBlock::DataBlock(vector<unsigned char> * v){
	this->initialize();
	this->data = v;
	this->data->push_back(0);
	this->remaining_bits_count=0;
}
DataBlock::DataBlock(vector<unsigned char> * v,unsigned char remaining_bits){
	this->initialize();
	this->data = v;
	this->remaining_bits_count=remaining_bits;
	if(!remaining_bits)
		this->data->push_back(0);
}

void DataBlock::addDataBlock(DataBlock* db) {
	unsigned int bitsToAdd = db->getSizeInBits();
	auto it = db->getIterator();
	while(bitsToAdd > 8){
		this->addByte(*it);
		it++;
		bitsToAdd = bitsToAdd - 8;
	}
	if(bitsToAdd){
		unsigned char aux= *it >> (8 - bitsToAdd);
		this->addBits(aux,bitsToAdd);
	}
}

void DataBlock::addBoolean(bool b) {
	if(b)
		this->addBits(0xFF,1);
	else
		this->addBits(0x00,1);
}

void DataBlock::initialize(){
	this->remaining_bits_count=0;
	unsigned char masks[] = {1,3,7,15,31,63,127,255};
	for (int i=0;i<8;i++)
		this->masks[i] = masks[i];
}

void DataBlock::addByte(unsigned char data) {
	if(!this->remaining_bits_count){
		this->data->at((this->data->size()-1)) = data;
		this->data->push_back(0);
	}
	else{
		this->addBits(data,8);
	}
}

void DataBlock::addBits(unsigned char data, unsigned char count) {
	//if (count>7)
	//	throw "No se pueden agregar mas de 7 bits con este metodo, usa addByte.";

	//Enmascaro los bits que contienen información
	data = data & this->masks[count-1];
	// No se arma byte
	if (this->remaining_bits_count + count < 8){
		this->data->at((this->data->size()-1)) =  this->data->at((this->data->size()-1)) | data << (8 - (count +	this->remaining_bits_count));
		this->remaining_bits_count+=count;
		return;
	}
	// Se arma byte
	if (this->remaining_bits_count + count == 8){
		this->data->at((this->data->size()-1)) =  this->data->at((this->data->size()-1)) | data;
		this->data->push_back(0);
		this->remaining_bits_count = 0;
		return;
	}
	// Se arma byte y sobran unos bits
	unsigned char new_byte=0;
	unsigned short int bits_to_shift = count - (8 - this->remaining_bits_count);
	this->data->at((this->data->size()-1)) =  this->data->at((this->data->size()-1)) | data >> bits_to_shift;
	//Alineao a izquierda lo que sobra y lo guardo
	new_byte = data << (8 - bits_to_shift);
	this->data->push_back(new_byte);
	//this->remaining_bits_count = count - bits_to_shift;
	this->remaining_bits_count = bits_to_shift;
}



unsigned long int DataBlock::getSizeInBytes() {
	if(this->remaining_bits_count == 0)
		return this->data->size() - 1;
	else
		return this->data->size();
}


unsigned long int DataBlock::getSizeInBits() {
		return (8*(this->data->size() -1) + this->remaining_bits_count);
}

vector<unsigned char>::iterator DataBlock::getIterator(){
	return this->data->begin();
}

DataBlock::~DataBlock() {
	delete this->data;
}

} /* namespace std */


