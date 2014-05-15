/*
 * CompressedFileReader.cpp
 *
 *  Created on: 14/05/2014
 *      Author: ari
 */

#include "CompressedFileReader.h"

namespace std {


CompressedFileReader::CompressedFileReader(string path) {
	this->nextBlockSizeInBits=0;
}

DataBlock* CompressedFileReader::getBlock() {
	DataBlock * db = nullptr;
	return db;
}

CompressedFileReader::~CompressedFileReader() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
