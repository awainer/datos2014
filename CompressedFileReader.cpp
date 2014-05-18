/*
 * CompressedFileReader.cpp
 *
 *  Created on: 14/05/2014
 *      Author: ari
 */

#include "CompressedFileReader.h"
#include <iostream>
namespace std {


CompressedFileReader::CompressedFileReader(string path) {
	//TODO chequeo
	this->fileStream.open(path.c_str(),ios::in | ios::binary);
	this->fileStream.read((char*) &(this->nextBlockSizeInBits), 4);

}

DataBlock* CompressedFileReader::getBlock() {
	//cerr << "NextBlockSize: " << this->nextBlockSizeInBits;
	DataBlock * db=NULL;
	vector<unsigned char> * vec; //= new vector<unsigned char>();
	vector<unsigned char>::iterator it;
	unsigned char remainingBits=0;
	unsigned int vecSize;

	vecSize = (this->nextBlockSizeInBits / 8);
	if (this->nextBlockSizeInBits % 8 > 0){
		vecSize+=1;
		remainingBits = this->nextBlockSizeInBits % 8;
	}
	vec = new vector<unsigned char>(vecSize + 4); //4 para header
	it = vec->begin();
	this->fileStream.read((char*)&(it[0]),vecSize+4);

	if(this->fileStream.eof()){
		this->nextBlockSizeInBits=0;
		vec->resize(this->fileStream.gcount());
	}else{
		//Extraigo los últimos 32 bits
		it = vec->begin();
		this->nextBlockSizeInBits = * (uint32_t*) &it[vecSize];
		//cerr << "NexBlockSizeBits: " << this->nextBlockSizeInBits << endl;
		vec->resize(vec->size() - 4 );
	}

	db = new DataBlock(vec, remainingBits);
	return db;
}

void CompressedFileReader::close() {
	this->fileStream.close();
}
bool CompressedFileReader::hasBlocksLeft() {
	return not this->fileStream.eof();
}

CompressedFileReader::~CompressedFileReader() {
	this->fileStream.close();
}

} /* namespace std */
