/*
 * RunLenght.cpp
 *
 *  Created on: 09/05/2014
 *      Author: ari
 */

#include "RunLenght.h"
#include "DataBlock.h"
#include  "iterator"
#include <iostream>


namespace std {

RunLenght::RunLenght() {
	// TODO Auto-generated constructor stub

}

RunLenght::~RunLenght() {
	// TODO Auto-generated destructor stub
}

DataBlock* RunLenght::encode(DataBlock* src) {
	DataBlock * db = new DataBlock();
	Run run;
	vector<unsigned char>::iterator it = src->getIterator();
	unsigned long int blockSize = src->getSizeInBytes();
	unsigned long int i = 0;
	//for(unsigned long int i=0; i < src->getSizeInBytes(); i++){

	while(i < blockSize){
		//Doble escape
		if(it[i] == this->escape){
			db->addByte(it[i]);
			db->addByte(it[i]);
			i+=1;
		}else{
			run = this->getRun(it,i);
			if(run.count > 3){
				this->encodeRun(db,run);
				i+=run.count;
			}else{
				db->addByte(it[i]);
				i+=1;
			}
		}
	run.count = 0;
	}
	return db;
}

DataBlock* RunLenght::decode(DataBlock* src) {
	DataBlock * db = new DataBlock();
	return db;
}

Run RunLenght::getRun(vector<unsigned char>::iterator it,
		unsigned long int position) {
	unsigned char count = 1;
	Run run = Run();
	run.symbol = it[position];
	position+=1;
	while(run.symbol == it[position] && count < 255){
		position+=1;
		count+=1;
	}
	run.count = count;
	return run;
}

void RunLenght::encodeRun(DataBlock* dst, Run r) {
	dst->addByte(this->escape);
	dst->addByte(r.symbol);
	dst->addByte(r.count);
}

} /* namespace std */

std::Run::Run() {
	this->symbol=0;
	this->count=0;
}

std::Run::~Run() {
}
